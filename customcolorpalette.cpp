#include "customcolorpalette.h"

CustomColorPalette::CustomColorPalette(int w, int h,QWidget *parent) : QWidget(parent)
{
   random.seed(QTime::currentTime().msecsSinceStartOfDay());
   bLayout = new QGridLayout(this);
   bLayout->setSpacing(0);
   bLayout->setMargin(0);
   setPaletteDimensions(w,h);
   bLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

bool CustomColorPalette::updateColors()
{
    int colorsNeed = paletteW * paletteH;
    int colorsHave = colorsUsed.length();
    while(colorsHave != colorsNeed) {
       if(colorsAvailable.empty()) return false;

       int randID = random.bounded(colorsAvailable.length());
       QColor colorNew = colorsAvailable[randID];

       colorsUsed.push_back(colorNew);
       colorsAvailable.remove(randID);

       QPushButton* buttonNew = paletteButtonCreate(colorNew);
       int rowID = colorsHave / paletteW;
       int colID = colorsHave % paletteW;
       bLayout->addWidget(buttonNew,rowID,colID);
       colorsHave++;
    }
    return true;
}

void CustomColorPalette::colorPressed(QColor color)
{
    emit colorPicked(color);
}

QPushButton *CustomColorPalette::paletteButtonCreate(QColor color)
{
    QPushButton* button = new PaletteButton(color,this);
    //To Do: Rework Into Special Button Class
    button->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
    connect(button,SIGNAL(colorClicked(QColor)),this,SLOT(colorPressed(QColor)));
    return button;
}

//void CustomColorPalette::paintEvent(QPaintEvent *event)
//{
//    QPainter painter(this);
//    QBrush brush;
//    painter.setBrush(brush);
//    double cellW = width() / paletteW;
//    double cellH = height() / paletteH;
//    for(int y = 0; y < paletteH; y++){
//        double drawY = y * cellH;
//        for(int x = 0; x < paletteH; x++) {
//            double drawX = x * cellW;
//            int colorID = y * paletteW + x;
//            QColor color = colorsUsed[colorID];
//            brush.setColor(color);
//            painter.drawRect(drawX,drawY,cellW,cellH);
//        }
//    }
//}
