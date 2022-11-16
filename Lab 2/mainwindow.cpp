#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(960,540);
    CWidget* cwidget = new CWidget();
    setCentralWidget(cwidget);
}

MainWindow::~MainWindow()
{
}



