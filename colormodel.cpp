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
    double C = (1 - R - K)/kReverse;
    double M = (1 - G - K)/kReverse;
    double Y = (1 - B - K)/kReverse;
    modelCMYK* color = new modelCMYK(C,M,Y,K);
    return color;
}

modelHSV *modelRGB::toHSV()
{
//    double maxChannel = std::max(R,G,B);
//    double minChannel = std::min(R,G,B);
//    double V = maxChannel;
//    double S = 1 - minChannel/maxChannel;
//    double H = 0;
//    double angleACOS = acos((R - 0.5 * G - 0.5 * B) / sqrt(R*R + G*G + B*B - R*G - R*B - G*B));
//    if(G >= B)
//    {
//        H = angleACOS / M_PI_2;
//    }
//    else
//    {
//        H = (1 - angleACOS) / M_PI_2;
//    }
//    return new modelHSV(H,S,V);
}

modelHLS *modelRGB::toHLS()
{

}

modelXYZ *modelRGB::toXYZ()
{

}

modelLAB *modelRGB::toLAB()
{

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
}

modelHLS *modelCMYK::toHLS()
{
    //To do
}

modelXYZ *modelCMYK::toXYZ()
{
    // To do
}

modelLAB *modelCMYK::toLAB()
{
    //To do
}
