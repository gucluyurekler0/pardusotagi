#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QListWidget>
#include <QJsonObject>
#include <QJsonArray>
#include <QUuid>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Her bir sohbetin yapısı
struct ChatSession {
    QString id;
    QString title;
    QJsonArray messages;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sendButton_clicked();
    void on_newChatButton_clicked();
    void on_chatListWidget_itemClicked(QListWidgetItem *item);
    void onResponseReceived(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager;

    // Aktif Sohbet Durumu
    QString currentChatId;
    QJsonArray currentMessages;
    bool isGeneratingTitle = false; // O anki istek başlık isteği mi?

    // Yardımcı Fonksiyonlar
    void createNewChat();
    void generateTitleForChat(const QString &firstPrompt);
    void saveChatToDisk(const QString &title);
    void loadAllChatsFromDisk();
    void displayChat(const QString &chatId);
};

#endif // MAINWINDOW_H