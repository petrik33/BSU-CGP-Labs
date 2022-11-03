#include "palettebutton.h"

PaletteButton::PaletteButton(QColor Color, QWidget *parent) : QPushButton(parent)
{
    color = Color;
    setStyleSheet("background-color: " + color.name());
    connect(this,SIGNAL(clicked(bool)),this,SLOT(clickedSlot(bool)));
}

void PaletteButton::clickedSlot(bool checked)
{
    emit colorClicked(color,checked);
}
