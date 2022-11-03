#ifndef COLORMODELBUTTON_H
#define COLORMODELBUTTON_H

#include <QWidget>
#include <QPushButton>
#include "colormodel.h"

class ColorModelButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ColorModelButton(QString text, COLOR_MODEL _modelID, QWidget *parent = nullptr);
    COLOR_MODEL getModelID() { return modelID; };
signals:
    void modelPicked(COLOR_MODEL modelID, bool checked);
protected slots:
    void clickedSlot(bool checked);
protected:
    COLOR_MODEL modelID;
};

#endif // COLORMODELBUTTON_H
