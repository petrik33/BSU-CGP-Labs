#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}

//const GLfloat letter::vertexData[vertices][3] = {
//    {0, 0, 0},
//    {0, 0, 0.25f},
//    {0.25f, 0, 0.25f},
//    {0.25f, 0, 0},

//    {0, 0.75f, 0},
//    {0, 0.75f, 0.25},
//    {0.25f, 0.75f, 0.25f},
//    {0.25f, 0.75f, 0},

//    {-0.25f, 0.75f, 0},
//    {-0.25f, 0.75f, 0.25f},
//    {0.25f, 0.75f, 0.25f},
//    {0.25f, 0.75f, 0},

//    {-0.25f, 1.0f, 0},
//    {-0.25f, 1.0f, 0.25f},
//    {0.25f, 1.0f, 0.25f},
//    {0.25f, 1.0f, 0}
//};
