#include "colorshowwidget.h"

ColorShowWidget::ColorShowWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(32,32);
}

void ColorShowWidget::setColor(QColor color)
{
    currentColor = color;
    update();
}

void ColorShowWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setBrush(QBrush(currentColor));
    painter.drawRect(rect());
}


