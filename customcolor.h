#ifndef CUSTOMCOLOR_H
#define CUSTOMCOLOR_H

#include <colormodel.h>
#include <QVector>

class customColor
{
public:
    customColor();
protected:
    QVector<colorModel*> representations;
};

#endif // CUSTOMCOLOR_H
