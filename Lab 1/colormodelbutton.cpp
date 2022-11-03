#include "colormodelbutton.h"

ColorModelButton::ColorModelButton(QString text, COLOR_MODEL _modelID, QWidget *parent) : QPushButton(text,parent)
{
    modelID = _modelID;
    connect(this,SIGNAL(clicked(bool)),this,SLOT(clickedSlot(bool)));
}

void ColorModelButton::clickedSlot(bool checked)
{
    emit modelPicked(modelID,checked);
}
