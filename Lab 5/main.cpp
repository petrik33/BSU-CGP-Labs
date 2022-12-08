#include "mainwindow.h"

#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("Lab 5");
    w.resize(900,900);

    QSize screenSize = qApp->screens()[0]->size();
    double x = (screenSize.width()-w.width()) / 2;
    double y = (screenSize.height()-w.height()) / 2;
    w.move(x, y);

    w.show();
    return a.exec();
}
