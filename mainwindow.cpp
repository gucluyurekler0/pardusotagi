#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    networkManager = new QNetworkAccessManager(this);

    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::on_sendButton_clicked);
    connect(ui->promptLineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_sendButton_clicked);
    connect(ui->newChatButton, &QPushButton::clicked, this, &MainWindow::on_newChatButton_clicked);
    connect(ui->chatListWidget, &QListWidget::itemClicked, this, &MainWindow::on_chatListWidget_itemClicked);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onResponseReceived);

    loadAllChatsFromDisk();
    createNewChat();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newChatButton_clicked()
{
    createNewChat();
}

void MainWindow::createNewChat()
{
    currentChatId = QUuid::createUuid().toString();
    currentMessages = QJsonArray();
    ui->chatHistoryTextEdit->clear();
    ui->promptLineEdit->clear();
}

void MainWindow::on_sendButton_clicked()
{
    QString prompt = ui->promptLineEdit->text().trimmed();
    if (prompt.isEmpty()) return;

    QString userHtml = QString(
                           "<div style='margin-bottom: 12px; background-color: #e9ecef; padding: 10px; border-radius: 8px;'>"
                           "<b style='color: #0d6efd;'>Siz:</b><br>%1"
                           "</div>"
                           ).arg(prompt.toHtmlEscaped().replace("\n", "<br>"));

    ui->chatHistoryTextEdit->append(userHtml);
    ui->promptLineEdit->clear();

    QJsonObject userMsg;
    userMsg["role"] = "user";
    userMsg["content"] = prompt;
    currentMessages.append(userMsg);

    ui->sendButton->setEnabled(false);
    ui->chatHistoryTextEdit->append("<div id='thinking' style='color: #6c757d; font-style: italic; margin-bottom: 8px;'>Yapay Zeka düşünüyor...</div>");

    if (currentMessages.size() == 1) {
        generateTitleForChat(prompt);
    }

    isGeneratingTitle = false;

    QUrl url("http://localhost:11434/api/generate");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    //json["model"] = "llama3.2";
    json["model"] = "qwen2.5:7b";
    json["prompt"] = prompt;
    json["stream"] = false;

    networkManager->post(request, QJsonDocument(json).toJson());
}

void MainWindow::generateTitleForChat(const QString &firstPrompt)
{
    isGeneratingTitle = true;

    QUrl url("http://localhost:11434/api/generate");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["model"] = "qwen2.5:3b";
    json["prompt"] = "Aşağıdaki mesaja göre maksimum 3-4 kelimelik kısa bir sohbet başlığı yaz. Sadece başlığı yaz: " + firstPrompt;
    json["stream"] = false;

    networkManager->post(request, QJsonDocument(json).toJson());
}


void MainWindow::onResponseReceived(QNetworkReply *reply)
{
    ui->sendButton->setEnabled(true);

    // "Düşünüyor..." yazısını kaldır
    QString currentText = ui->chatHistoryTextEdit->toHtml();
    currentText.remove("<div id=\"thinking\" style=\"color: #6c757d; font-style: italic; margin-bottom: 8px;\">Yapay Zeka düşünüyor...</div>");
    ui->chatHistoryTextEdit->setHtml(currentText);

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QJsonObject jsonObj = QJsonDocument::fromJson(responseData).object();
        QString aiResponse = jsonObj["response"].toString().trimmed();

        if (isGeneratingTitle) {
            // Başlık üretme isteği tamamlandı: Başlığı kaydet ve listeyi tazele
            isGeneratingTitle = false;
            saveChatToDisk(aiResponse);
        } else {
            // Normal sohbet yanıtı geldiyse ekrana ekle
            QString formattedResponse = aiResponse.toHtmlEscaped().replace("\n", "<br>");

            QString aiHtml = QString(
                                 "<div style='margin-bottom: 16px; background-color: #f8f9fa; border-left: 4px solid #198754; padding: 12px; border-radius: 6px; line-height: 1.5;'>"
                                 "<b style='color: #198754;'>Pardus Otağı AI:</b><br><br>%1"
                                 "</div>"
                                 ).arg(formattedResponse);

            ui->chatHistoryTextEdit->append(aiHtml);

            // Yanıtı mesaj geçmişine ekle
            QJsonObject aiMsg;
            aiMsg["role"] = "assistant";
            aiMsg["content"] = aiResponse;
            currentMessages.append(aiMsg);

            // Başlığı değiştirmeden (mevcut başlığı koruyarak) diske kaydet
            saveChatToDisk(currentChatTitle);
        }
    } else {
        ui->chatHistoryTextEdit->append("<div style='color: red; margin-bottom: 10px;'><b>Hata:</b> Ollama sunucusuna bağlanılamadı!</div>");
        isGeneratingTitle = false;
    }
    reply->deleteLater();
}


void MainWindow::saveChatToDisk(const QString &title)
{
    // Yalnızca gelen başlık doluysa başlığı güncelle
    if (!title.isEmpty()) {
        currentChatTitle = title;
    }

    QFile file("chats.json");
    QJsonObject allChats;

    if (file.open(QIODevice::ReadOnly)) {
        allChats = QJsonDocument::fromJson(file.readAll()).object();
        file.close();
    }

    QJsonObject singleChat;
    singleChat["id"] = currentChatId;

    // Eğer üretilmiş bir başlık yoksa geçici olarak "Yeni Sohbet" yaz, üretildiyse üretilen başlığı koy
    singleChat["title"] = currentChatTitle.isEmpty() ? "Yeni Sohbet" : currentChatTitle;
    singleChat["messages"] = currentMessages;

    allChats[currentChatId] = singleChat;

    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(allChats).toJson());
        file.close();
    }

    // Sol listedeki sohbetleri ekrana yeniden yükle
    loadAllChatsFromDisk();
}



void MainWindow::loadAllChatsFromDisk()
{
    ui->chatListWidget->clear();

    QFile file("chats.json");
    if (!file.open(QIODevice::ReadOnly)) return;

    QJsonObject allChats = QJsonDocument::fromJson(file.readAll()).object();
    file.close();

    for (const QString &key : allChats.keys()) {
        QJsonObject chat = allChats[key].toObject();
        QListWidgetItem *item = new QListWidgetItem(chat["title"].toString());
        item->setData(Qt::UserRole, chat["id"].toString());
        ui->chatListWidget->insertItem(0, item);
    }
}


void MainWindow::on_chatListWidget_itemClicked(QListWidgetItem *item)
{
    QString selectedId = item->data(Qt::UserRole).toString();
    displayChat(selectedId);
}


void MainWindow::displayChat(const QString &chatId)
{
    QFile file("chats.json");
    if (!file.open(QIODevice::ReadOnly)) return;

    QJsonObject allChats = QJsonDocument::fromJson(file.readAll()).object();
    file.close();

    if (!allChats.contains(chatId)) return;

    QJsonObject chat = allChats[chatId].toObject();
    currentChatId = chatId;
    currentMessages = chat["messages"].toArray();

    ui->chatHistoryTextEdit->clear();
    for (const QJsonValue &val : currentMessages) {
        QJsonObject msg = val.toObject();
        QString role = msg["role"].toString();
        QString content = msg["content"].toString().toHtmlEscaped().replace("\n", "<br>");

        if (role == "user") {
            ui->chatHistoryTextEdit->append(QString(
                                                "<div style='margin-bottom: 12px; background-color: #e9ecef; padding: 10px; border-radius: 8px;'>"
                                                "<b style='color: #0d6efd;'>Siz:</b><br>%1"
                                                "</div>"
                                                ).arg(content));
        } else {
            ui->chatHistoryTextEdit->append(QString(
                                                "<div style='margin-bottom: 16px; background-color: #f8f9fa; border-left: 4px solid #198754; padding: 12px; border-radius: 6px; line-height: 1.5;'>"
                                                "<b style='color: #198754;'>Pardus Otağı AI:</b><br><br>%1"
                                                "</div>"
                                                ).arg(content));
        }
    }
}