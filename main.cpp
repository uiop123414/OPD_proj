#include "mainwindow_red.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwindow_red w;
    w.show();
    return a.exec();
}
