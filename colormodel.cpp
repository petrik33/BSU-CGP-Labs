#include "colormodel.h"

colorModel::colorModel()
{
    //
}

QString colorModel::ColorModelName(int id)
{
    QVector<QString> paramNames = colorModelsParamNames[id];
    int paramNum = paramNames.length();
    QString name;
    for(int i = 0; i < paramNum;i++){
        name += paramNames[i];
    }
    return name;
}

colorModel* colorModel::makeColorModel(COLOR_MODEL id) {
    switch (id) {
    case COLOR_MODEL::RGB:
        return new modelRGB();
        break;
    case COLOR_MODEL::CMYK:
        return new modelCMYK();
        break;
    case COLOR_MODEL::HLS:
        return new modelHLS();
        break;
    case COLOR_MODEL::HSV:
        return new modelHSV();
        break;
    case COLOR_MODEL::XYZ:
        return new modelXYZ();
        break;
    case COLOR_MODEL::LAB:
        return new modelLAB();
        break;
    default:
        return nullptr;
        break;
    }
}

colorModel* colorModel::convertColorModel(COLOR_MODEL id) {
    switch (id) {
    case COLOR_MODEL::RGB:
        return toRGB();
        break;
    case COLOR_MODEL::CMYK:
        return toCMYK();
        break;
    case COLOR_MODEL::HLS:
        return toHLS();
        break;
    case COLOR_MODEL::HSV:
        return toHSV();
        break;
    case COLOR_MODEL::XYZ:
        return toXYZ();
        break;
    case COLOR_MODEL::LAB:
        return toLAB();
        break;
    default:
        return nullptr;
        break;
    }
}

void colorModel::setParams(double *newParams)
{
    for(int i = 0; i < colorModelsMaxParams; i++) {
        params[i] = newParams[i];
    }
}

modelCMYK *modelRGB::toCMYK()
{
    double R = params[0];
    double G = params[1];
    double B = params[2];

    double K = qMin(qMin(1 - R, 1 - G), 1 - B);
    double kReverse = 1 - K;
    if(kReverse == 0) return new modelCMYK(); // Only Happens with Black Color (Default)
    double C = (1 - R - K)/kReverse;
    double M = (1 - G - K)/kReverse;
    double Y = (1 - B - K)/kReverse;
    modelCMYK* color = new modelCMYK(C,M,Y,K);

    return color;
}

modelHSV *modelRGB::toHSV()
{
    double R = params[0];
    double G = params[1];
    double B = params[2];

    double maxChannel = qMax(qMax(R,G),B);
    double minChannel = qMin(qMin(R,G),B);
    double V = maxChannel;

    double S = 1 - minChannel/maxChannel;
    double H = 0;

    double angleACOS = acos((R - 0.5 * G - 0.5 * B) / sqrt(R*R + G*G + B*B - R*G - R*B - G*B));
    if(G >= B)
    {
        H = angleACOS / M_PI_2;
    }
    else
    {
        H = (1 - angleACOS) / M_PI_2;
    }

    return new modelHSV(H,S,V);
}

modelHLS *modelRGB::toHLS()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelHLS();
}

modelXYZ *modelRGB::toXYZ()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelXYZ();
}

modelLAB *modelRGB::toLAB()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelLAB();
}

modelRGB *modelCMYK::toRGB()
{
    double C = params[0];
    double M = params[1];
    double Y = params[2];
    double K = params[3];

    double kReverse = 1 - K;
    double R = (1 - C)/kReverse;
    double G = (1 - M)/kReverse;
    double B = (1 - Y)/kReverse;

    return new modelRGB(R,G,B);
}

modelHSV *modelCMYK::toHSV()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelHSV();
}

modelHLS *modelCMYK::toHLS()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelHLS();
}

modelXYZ *modelCMYK::toXYZ()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelXYZ();
}

modelLAB *modelCMYK::toLAB()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelLAB();
}

modelRGB* modelHSV::toRGB()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelRGB();
}

modelCMYK* modelHSV::toCMYK()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelCMYK();
}

modelHLS *modelHSV::toHLS()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelHLS();
}

modelXYZ *modelHSV::toXYZ()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelXYZ();
}

modelLAB *modelHSV::toLAB()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelLAB();
}

modelRGB* modelHLS::toRGB()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelRGB();
}

modelCMYK* modelHLS::toCMYK()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelCMYK();
}

modelHSV *modelHLS::toHSV()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelHSV();
}

modelXYZ *modelHLS::toXYZ()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelXYZ();
}

modelLAB *modelHLS::toLAB()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelLAB();
}

modelRGB* modelXYZ::toRGB()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelRGB();
}

modelCMYK* modelXYZ::toCMYK()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelCMYK();
}

modelHSV *modelXYZ::toHSV()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelHSV();
}

modelHLS *modelXYZ::toHLS()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelHLS();
}

modelLAB *modelXYZ::toLAB()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelLAB();
}

modelRGB* modelLAB::toRGB()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelRGB();
}

modelCMYK* modelLAB::toCMYK()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelCMYK();
}

modelHSV *modelLAB::toHSV()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelHSV();
}

modelHLS *modelLAB::toHLS()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelHLS();
}

modelXYZ *modelLAB::toXYZ()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelXYZ();
}

