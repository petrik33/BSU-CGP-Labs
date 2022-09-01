#ifndef ENUMCOLORMODEL_H
#define ENUMCOLORMODEL_H

#include <QObject>


class enumColorModel
{
    Q_GADGET
public:
    enum ColorModel {
        RGB,
        CMYK,
        HSV,
        HLS,
        XYZ,
        LAB
    };
    Q_ENUM(ColorModel);
private:
    explicit enumColorModel(QObject* parent = nullptr);
};

#endif // ENUMCOLORMODEL_H
