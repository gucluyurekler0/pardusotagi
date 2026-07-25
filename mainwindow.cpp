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

    // Ağ isteklerini yönetecek nesne
    networkManager = new QNetworkAccessManager(this);

    // SİNYAL-SLOT BAĞLANTILARI (Buton ve Enter tuşunu bağlayan kısım)
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::on_sendButton_clicked);
    connect(ui->promptLineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_sendButton_clicked);
    connect(ui->newChatButton, &QPushButton::clicked, this, &MainWindow::on_newChatButton_clicked);
    connect(ui->chatListWidget, &QListWidget::itemClicked, this, &MainWindow::on_chatListWidget_itemClicked);

    // Ağ yanıtı geldiğinde tetiklenecek slot
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onResponseReceived);

    // Uygulama açılınca geçmişi yükle ve yeni sohbet başlat
    loadAllChatsFromDisk();
    createNewChat();
}

MainWindow::~MainWindow() {
    delete ui;
}

// 🆕 Yeni Sohbet Butonu
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

// 📤 Mesaj Gönderme
void MainWindow::on_sendButton_clicked()
{
    QString prompt = ui->promptLineEdit->text().trimmed();
    if (prompt.isEmpty()) return;

    // Ekrana kullanıcı mesajını yaz
    ui->chatHistoryTextEdit->append("<b>Siz:</b> " + prompt);
    ui->promptLineEdit->clear();

    QJsonObject userMsg;
    userMsg["role"] = "user";
    userMsg["content"] = prompt;
    currentMessages.append(userMsg);

    // İşlem yapılırken kullanıcıyı bilgilendir
    ui->sendButton->setEnabled(false);
    ui->chatHistoryTextEdit->append("<i>Yapay Zeka düşünüyor...</i>");

    // Eğer sohbetin ilk mesajıysa başlık üret
    if (currentMessages.size() == 1) {
        generateTitleForChat(prompt);
    }

    // Ollama'ya isteği at
    isGeneratingTitle = false;

    QUrl url("http://localhost:11434/api/generate");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["model"] = "llama3.2"; // Arka planda indirdiğiniz model adı (örn: "phi3" ise "phi3" yazın)
    json["prompt"] = prompt;
    json["stream"] = false;

    networkManager->post(request, QJsonDocument(json).toJson());
}

// 🏷️ Başlık Üretme
void MainWindow::generateTitleForChat(const QString &firstPrompt)
{
    isGeneratingTitle = true;

    QUrl url("http://localhost:11434/api/generate");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["model"] = "llama3.2";
    json["prompt"] = "Aşağıdaki mesaja göre maksimum 3-4 kelimelik kısa bir sohbet başlığı yaz. Sadece başlığı yaz: " + firstPrompt;
    json["stream"] = false;

    networkManager->post(request, QJsonDocument(json).toJson());
}

// 📩 Yanıt Geldiğinde
void MainWindow::onResponseReceived(QNetworkReply *reply)
{
    ui->sendButton->setEnabled(true);

    // "Düşünüyor..." yazısını kaldır
    QString currentText = ui->chatHistoryTextEdit->toHtml();
    currentText.remove("<i>Yapay Zeka düşünüyor...</i>");
    ui->chatHistoryTextEdit->setHtml(currentText);

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QJsonObject jsonObj = QJsonDocument::fromJson(responseData).object();
        QString aiResponse = jsonObj["response"].toString().trimmed();

        if (isGeneratingTitle) {
            saveChatToDisk(aiResponse);
            isGeneratingTitle = false;
        } else {
            ui->chatHistoryTextEdit->append("<b>Yapay Zeka:</b> " + aiResponse + "<br>");

            QJsonObject aiMsg;
            aiMsg["role"] = "assistant";
            aiMsg["content"] = aiResponse;
            currentMessages.append(aiMsg);
        }
    } else {
        ui->chatHistoryTextEdit->append("<font color='red'><b>Hata:</b> Ollama sunucusuna bağlanılamadı! Arka planda açık olduğundan emin olun.</font><br>");
    }
    reply->deleteLater();
}

// 💾 JSON Kayıt
void MainWindow::saveChatToDisk(const QString &title)
{
    QFile file("chats.json");
    QJsonObject allChats;

    if (file.open(QIODevice::ReadOnly)) {
        allChats = QJsonDocument::fromJson(file.readAll()).object();
        file.close();
    }

    QJsonObject singleChat;
    singleChat["id"] = currentChatId;
    singleChat["title"] = title;
    singleChat["messages"] = currentMessages;

    allChats[currentChatId] = singleChat;

    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(allChats).toJson());
        file.close();
    }

    loadAllChatsFromDisk();
}

// 📂 Kayıtları Yükleme
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

// 🖱️ Listeden Seçim
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
        QString role = msg["role"].toString() == "user" ? "<b>Siz:</b> " : "<b>Yapay Zeka:</b> ";
        ui->chatHistoryTextEdit->append(role + msg["content"].toString() + "<br>");
    }
}