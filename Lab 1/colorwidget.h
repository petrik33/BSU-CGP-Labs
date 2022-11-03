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
#include <customcolorpalette.h>
#include <colormodelbutton.h>

class ColorWidget : public QWidget
{
    Q_OBJECT
public:
   ColorWidget(QWidget *parent = nullptr);
public slots:
   void setColorModel(COLOR_MODEL modelID);
   void changeColor(QColor);
   void colorModelUpdateSliders();
   void colorModelUpdateSpins();
   void ColorModelSet(QVector<double> params);
   void spinsSlidersSet();
   void colorModelUpdatePalette(QColor color);
//   void onConversion(bool inaccurate);
protected:
   bool slidersSetInner;
   bool spinsSetInner;
   QGridLayout* mainLayout = nullptr;
   ColorShowWidget* cShow = nullptr;
   CustomColorPalette* cPalette = nullptr;
   QVector<ColorModelButton*> cSpaceButtons;
   QVector<QLabel*> cLabels;
   QVector<QSlider*> cSliders;
   QVector<QSpinBox*> cSpins;
   colorModel* colorModelInst = nullptr;
   COLOR_MODEL colorModelENUM = COLOR_MODEL::RGB;
   int getParamsNum () const {
       int paramsNum = 3;
       if(colorModelENUM == COLOR_MODEL::CMYK) paramsNum = 4;
       return paramsNum;
   }
};

const int xDimension = 12;
const int yDimension = 9;

const int cShowX = 0;
const int cShowY = 0;
const int cShowColSpan = 8;
const int cShowRowSpan = 4;

const int paletteX = 8;
const int paletteY = 0;
const int paletteColSpan = 4;
const int paletteRowSpan = 4;

const int buttonsX = cShowX;
const int buttonsY = cShowY + cShowRowSpan;
const int buttonsInRow = 3;
const int buttonsRowSpan = 1;
const int buttonsColSpan = 4;

const int labelsX = 0;
const int labelsY = buttonsY+buttonsRowSpan*(int(COLOR_MODEL::MODELS_NUMBER) / buttonsInRow);
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
