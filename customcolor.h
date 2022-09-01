#ifndef CUSTOMCOLOR_H
#define CUSTOMCOLOR_H

#include <enumcolormodel.h>
#include <colormodel.h>
#include <QVector>

typedef enumColorModel::ColorModel Model;

class customColor
{
public:
    customColor();
protected:
    QVector<colorModel*> representations;
};

#endif // CUSTOMCOLOR_H
