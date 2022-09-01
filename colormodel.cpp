#include "colormodel.h"

colorModel::colorModel()
{
    //
}

modelCMYK *modelRGB::toCMYK()
{
    double K = std::min(1 - R, 1 - G, 1 - B);
    double kReverse = 1 - K;
    double C = (1 - R - K)/kReverse;
    double M = (1 - G - K)/kReverse;
    double Y = (1 - B - K)/kReverse;
    modelCMYK* color = new modelCMYK(C,M,Y,K);
    return color;
}

modelHSV *modelRGB::toHSV()
{
    //
}
