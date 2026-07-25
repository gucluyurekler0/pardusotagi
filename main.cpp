#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show(); // Pencereyi ekranda göster

    return a.exec(); // Uygulama döngüsünü başlat
}