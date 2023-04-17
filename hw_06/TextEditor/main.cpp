#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QFile style(":/styles/aquaTheme.qss");
    style.open(QFile::ReadOnly);
    qApp->setStyleSheet(style.readAll());
    style.close();
    w.show();
    return a.exec();
}
