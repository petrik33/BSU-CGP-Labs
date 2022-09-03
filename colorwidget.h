#ifndef COLORWINDOW_H
#define COLORWINDOW_H

#include <QWidget>
#include <QPainter>

#include <QVector>
#include <QColor>

#include <QGridLayout>
#include <QSpacerItem>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>

#include <colorshowwidget.h>
#include <colormodel.h>
#include <enumcolormodel.h>

class ColorWidget : public QWidget
{
    Q_OBJECT
public:
   ColorWidget(QWidget *parent = nullptr);
   enum ColorModel {
       RGB = 0,
       CMYK,
       HSV,
       HLS,
       XYZ,
       LAB,
       MODELS_NUMBER
   };
   Q_ENUM(ColorModel);
public slots:
   void setColorModel(ColorModel modelID);
protected:
   QGridLayout* mainLayout = nullptr;
   ColorShowWidget* cShow = nullptr;
   QVector<QPushButton*> cSpaceButtons;
   QVector<QLabel*> cLabels;
   QVector<QSlider*> cSliders;
   QVector<QSpinBox*> cSpins;
};

const int xDimension = 12;
const int yDimension = 9;

const int cShowX = 0;
const int cShowY = 0;
const int cShowColSpan = 8;
const int cShowRowSpan = 4;

const int buttonsX = cShowX;
const int buttonsY = cShowY + cShowRowSpan;
const int buttonsInRow = 3;
const int buttonsRowSpan = 1;
const int buttonsColSpan = 4;

const int labelsX = 0;
const int labelsY = buttonsY+buttonsRowSpan*(int(ColorWidget::MODELS_NUMBER) / buttonsInRow);
const int labelsColSpan = 2;
const int labelsRowSpan = 1;

const int slidersX = labelsX + labelsColSpan;
const int slidersY = labelsY;
const int slidersColSpan = 8;
const int slidersRowSpan = 1;

const int spinsX = slidersX + slidersColSpan;
const int spinsY = labelsY;
const int spinsColSpan = 2;
const int spinsRowSpan = 1;

#endif // COLORWINDOW_H
