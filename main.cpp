#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    int width = QApplication::desktop()->width();
    int height = QApplication::desktop()->height();
    int x=(width - w.width()) / 2.0;
    int y=(height - w.height()) / 2.0;
    w.setGeometry(x,y,w.width(),w.height());
    w.show();
    return a.exec();
}
