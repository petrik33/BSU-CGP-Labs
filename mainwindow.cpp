#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ColorWidget* cWidget = new ColorWidget(this);
    setCentralWidget(cWidget);
    int baseSize = 96;
    resize(baseSize * xDimension,baseSize * yDimension);
}

MainWindow::~MainWindow()
{
    //
}

