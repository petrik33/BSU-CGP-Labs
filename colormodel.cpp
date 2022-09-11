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

modelCMYK *modelRGB::toCMYK()
{
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
    //To do
    return new modelHLS();
}

modelXYZ *modelRGB::toXYZ()
{
    //To do
    return new modelXYZ();
}

modelLAB *modelRGB::toLAB()
{
    //To do
    return new modelLAB();
}

modelRGB *modelCMYK::toRGB()
{
    double kReverse = 1 - K;
    double R = (1 - C)/kReverse;
    double G = (1 - M)/kReverse;
    double B = (1 - Y)/kReverse;
    return new modelRGB(R,G,B);
}

modelHSV *modelCMYK::toHSV()
{
    //To do
    return new modelHSV();
}

modelHLS *modelCMYK::toHLS()
{
    //To do
    return new modelHLS();
}

modelXYZ *modelCMYK::toXYZ()
{
    // To do
    return new modelXYZ();
}

modelLAB *modelCMYK::toLAB()
{
    //To do
    return new modelLAB();
}

modelRGB* modelHSV::toRGB()
{
    // To do
    return new modelRGB();
}

modelCMYK* modelHSV::toCMYK()
{
    // To do
    return new modelCMYK();
}

modelHLS *modelHSV::toHLS()
{
    //To do
    return new modelHLS();
}

modelXYZ *modelHSV::toXYZ()
{
    // To do
    return new modelXYZ();
}

modelLAB *modelHSV::toLAB()
{
    //To do
    return new modelLAB();
}

modelRGB* modelHLS::toRGB()
{
    // To do
    return new modelRGB();
}

modelCMYK* modelHLS::toCMYK()
{
    // To do
    return new modelCMYK();
}

modelHSV *modelHLS::toHSV()
{
    // To do
    return new modelHSV();
}

modelXYZ *modelHLS::toXYZ()
{
    // To do
    return new modelXYZ();
}

modelLAB *modelHLS::toLAB()
{
    //To do
    return new modelLAB();
}

modelRGB* modelXYZ::toRGB()
{
    // To do
    return new modelRGB();
}

modelCMYK* modelXYZ::toCMYK()
{
    // To do
    return new modelCMYK();
}

modelHSV *modelXYZ::toHSV()
{
    // To do
    return new modelHSV();
}

modelHLS *modelXYZ::toHLS()
{
    //To do
    return new modelHLS();
}

modelLAB *modelXYZ::toLAB()
{
    //To do
    return new modelLAB();
}

modelRGB* modelLAB::toRGB()
{
    // To do
    return new modelRGB();
}

modelCMYK* modelLAB::toCMYK()
{
    // To do
    return new modelCMYK();
}

modelHSV *modelLAB::toHSV()
{
    // To do
    return new modelHSV();
}

modelHLS *modelLAB::toHLS()
{
    //To do
    return new modelHLS();
}

modelXYZ *modelLAB::toXYZ()
{
    //To do
    return new modelXYZ();
}

