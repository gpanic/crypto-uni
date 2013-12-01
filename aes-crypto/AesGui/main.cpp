#include "mainwindow.h"
#include <QApplication>
#include <aes2.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Aes::CreateKey("D:/testkey.key", 128);

    return a.exec();
}
