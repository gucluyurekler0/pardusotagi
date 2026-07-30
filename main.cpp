#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   
    a.setStyleSheet(R"(
     
        QMainWindow, QWidget {
            background-color: #f8f9fa;
            color: #212529;
            font-family: 'Segoe UI', Ubuntu, sans-serif;
        }

   
        QListWidget {
            background-color: #ffffff;
            border: 1px solid #dee2e6;
            border-radius: 8px;
            color: #212529;
            font-size: 13px;
            outline: none;
            padding: 4px;
        }
        QListWidget::item {
            padding: 10px;
            border-bottom: 1px solid #f1f3f5;
            border-radius: 6px;
            margin-bottom: 2px;
        }
        QListWidget::item:hover {
            background-color: #e9ecef;
            color: #000000;
        }
        QListWidget::item:selected {
            background-color: #0d6efd;
            color: #ffffff;
            font-weight: bold;
        }

       
        QPushButton {
            background-color: #0d6efd;
            color: #ffffff;
            border: none;
            border-radius: 6px;
            padding: 8px 16px;
            font-weight: 600;
            font-size: 13px;
        }
        QPushButton:hover {
            background-color: #0b5ed7;
        }
        QPushButton:pressed {
            background-color: #0a58ca;
        }
        QPushButton:disabled {
            background-color: #ced4da;
            color: #6c757d;
        }

        /* Sohbet Ekranı (QTextEdit) */
        QTextEdit {
            background-color: #ffffff;
            border: 1px solid #dee2e6;
            border-radius: 8px;
            color: #212529;
            font-size: 14px;
            padding: 12px;
        }

     
        QLineEdit {
            background-color: #ffffff;
            border: 1px solid #ced4da;
            border-radius: 6px;
            padding: 9px 12px;
            color: #212529;
            font-size: 14px;
        }
        QLineEdit:focus {
            border: 2px solid #0d6efd;
        }
    )");

    MainWindow w;
    w.show();

    return a.exec();
}
