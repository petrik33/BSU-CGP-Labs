#include "colorshowwidget.h"

ColorShowWidget::ColorShowWidget(QWidget *parent) : QWidget(parent)
{
    inaccurate = false;
    setMinimumSize(32,32);
}

void ColorShowWidget::setColor(QColor color)
{
    currentColor = color;
    update();
}

void ColorShowWidget::setInaccurate(bool on)
{
    inaccurate = on;
}

void ColorShowWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    QBrush brush(currentColor);

    if(inaccurate) {
        QColor lowAlphaColor = currentColor;
        lowAlphaColor.setAlpha(128);
        painter.setBrush(QBrush(lowAlphaColor));

        painter.drawRect(rect());
        painter.drawText(rect(),Qt::AlignCenter,text);

        return;
    }

    painter.setBrush(QBrush(currentColor));
    painter.drawRect(rect());

}


