#ifndef PALETTEBUTTON_H
#define PALETTEBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QColor>

class PaletteButton : public QPushButton
{
    Q_OBJECT
public:
    explicit PaletteButton(QColor Color, QWidget *parent = nullptr);
signals:
    void colorClicked(QColor color, bool checked = false);
protected slots:
    void clickedSlot(bool checked);
protected:
    QColor color;
};

#endif // PALETTEBUTTON_H
