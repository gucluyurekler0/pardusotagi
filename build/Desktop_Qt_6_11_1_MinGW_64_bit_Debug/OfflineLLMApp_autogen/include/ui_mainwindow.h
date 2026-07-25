/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *mainHorizontalLayout;
    QVBoxLayout *leftPanelLayout;
    QPushButton *newChatButton;
    QListWidget *chatListWidget;
    QVBoxLayout *rightPanelLayout;
    QTextEdit *chatHistoryTextEdit;
    QHBoxLayout *inputHorizontalLayout;
    QLineEdit *promptLineEdit;
    QPushButton *sendButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(950, 650);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainHorizontalLayout = new QHBoxLayout(centralwidget);
        mainHorizontalLayout->setObjectName("mainHorizontalLayout");
        leftPanelLayout = new QVBoxLayout();
        leftPanelLayout->setObjectName("leftPanelLayout");
        newChatButton = new QPushButton(centralwidget);
        newChatButton->setObjectName("newChatButton");

        leftPanelLayout->addWidget(newChatButton);

        chatListWidget = new QListWidget(centralwidget);
        chatListWidget->setObjectName("chatListWidget");

        leftPanelLayout->addWidget(chatListWidget);


        mainHorizontalLayout->addLayout(leftPanelLayout);

        rightPanelLayout = new QVBoxLayout();
        rightPanelLayout->setObjectName("rightPanelLayout");
        chatHistoryTextEdit = new QTextEdit(centralwidget);
        chatHistoryTextEdit->setObjectName("chatHistoryTextEdit");
        chatHistoryTextEdit->setReadOnly(true);

        rightPanelLayout->addWidget(chatHistoryTextEdit);

        inputHorizontalLayout = new QHBoxLayout();
        inputHorizontalLayout->setObjectName("inputHorizontalLayout");
        promptLineEdit = new QLineEdit(centralwidget);
        promptLineEdit->setObjectName("promptLineEdit");

        inputHorizontalLayout->addWidget(promptLineEdit);

        sendButton = new QPushButton(centralwidget);
        sendButton->setObjectName("sendButton");

        inputHorizontalLayout->addWidget(sendButton);


        rightPanelLayout->addLayout(inputHorizontalLayout);


        mainHorizontalLayout->addLayout(rightPanelLayout);

        mainHorizontalLayout->setStretch(0, 1);
        mainHorizontalLayout->setStretch(1, 3);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Pardus Ota\304\237\304\261", nullptr));
        newChatButton->setText(QCoreApplication::translate("MainWindow", "+ Yeni Sohbet", nullptr));
        promptLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Bir \305\237eyler sorun...", nullptr));
        sendButton->setText(QCoreApplication::translate("MainWindow", "G\303\266nder", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
