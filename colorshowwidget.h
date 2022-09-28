#ifndef COLORSHOWWIDGET_H
#define COLORSHOWWIDGET_H

#include <QWidget>
#include <QPainter>

class ColorShowWidget : public QWidget
{
    Q_OBJECT
public:
    ColorShowWidget(QWidget *parent = nullptr);
public slots:
   void setColor(QColor color);
   void setInaccurate(bool on);
protected:
    void paintEvent(QPaintEvent *event) override;
    QColor currentColor;
    bool inaccurate;
    const QString text = "APPROXIMATED";
};

#endif // COLORSHOWWIDGET_H
