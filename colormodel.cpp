#include "colormodel.h"

colorModel::colorModel()
{
    params.fill(0,colorModelsMaxParams);
}

colorModel::colorModel(QVector<double> Params)
{
    params = Params;
    if(params.size() < colorModelsMaxParams) params.push_back(0);
}

colorModel::~colorModel()
{

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

QVector<double>colorModel::getParams()
{
    return params;
}

QColor colorModel::getQColor()
{
    modelRGB* rgb = toRGB();
    QVector<double> params = rgb->getParams();
    return QColor(params[0]*255,params[1]*255,params[2]*255);
}

void colorModel::setParams(QVector<double> newParams)
{
    int paramsNum = newParams.size();
    for(int i = 0; i < paramsNum; i++) {
        params[i] = newParams[i];
    }
}

QVector<double> modelRGB::rgbToHueMaxMin(QVector<double> params) {
    double r = params[0];
    double g = params[1];
    double b = params[2];

    auto result = std::minmax_element(params.begin(),params.end()-1);
    int maxIndex = result.second - params.begin();

    double min = *result.first;
    double max = *result.second;

    double c = max - min;

    double hue = 0;
    double segment;
    double shift;

    if (c > 0) {
        switch(maxIndex) {
          case 0:
            segment = (g - b) / c;
            shift   = 0 / 60;       // R° / (360° / hex sides)
            if (segment < 0) {          // hue > 180, full rotation
              shift = 360 / 60;         // R° / (360° / hex sides)
            }
            break;
          case 1:
            segment = (b - r) / c;
            shift   = 120 / 60;     // G° / (360° / hex sides)
            break;
          case 2:
            segment = (r - g) / c;
            shift   = 240 / 60;     // B° / (360° / hex sides)
            break;
        }
        hue = segment + shift;
    }

    QVector<double> hueMaxMin = {hue / 6, max, min};
    return hueMaxMin; // hue is in [0,6], normalize it
}

QVector<double> modelRGB::rgbFromCXH(double C, double X, double H)
{
    QVector<double> rgb;
    QVector<double> cxo = {C, X, 0};
    switch (int(floor(H * 6))) {
    case 0:
        //remain default: cxo
        break;
    case 1:
        //xco
        cxo.swapItemsAt(0,1);
        break;
    case 2:
        //ocx
        cxo.swapItemsAt(0,1);
        cxo.swapItemsAt(0,2);
        break;
    case 3:
        //oxc
        cxo.swapItemsAt(0,2);
        break;
    case 4:
        //xoc
        cxo.swapItemsAt(0,2);
        cxo.swapItemsAt(0,1);
        break;
    case 5:
    case 6:
        //cox
        cxo.swapItemsAt(1,2);
        break;

    }
    for(int i = 0; i < 3; i++) {
        rgb.push_back(cxo[i]);
    }
    return rgb;
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
    QVector<double> hueMaxMin = modelRGB::rgbToHueMaxMin(params);

    double H = hueMaxMin[0];

    double maxChannel = hueMaxMin[1];
    double minChannel = hueMaxMin[2];

    double remainder = (maxChannel == 0) ? 0 : minChannel / maxChannel;

    double S = 1 - remainder;
    double V = maxChannel;

    return new modelHSV(H,S,V);
}

modelHLS *modelRGB::toHLS()
{
    QVector<double> hueMaxMin = modelRGB::rgbToHueMaxMin(params);

    double H = hueMaxMin[0];

    double maxChannel = hueMaxMin[1];
    double minChannel = hueMaxMin[2];

    double delta = maxChannel - minChannel;

    double L = (maxChannel + minChannel) / 2;
    double divider = (1 - abs(2*L - 1));
    double S = (divider == 0) ? 0 : delta / divider;

    return new modelHLS(H,L,S);
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
    double R = (1 - C)*kReverse;
    double G = (1 - M)*kReverse;
    double B = (1 - Y)*kReverse;

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
    double H = params[0];
    double S = params[1];
    double V = params[2];

    double C = V * S;
    double X = C * (1 - abs(fmod(H*6,2.0) - 1));

    QVector<double> rgbParams = modelRGB::rgbFromCXH(C,X,H);

    double m = V - C;

    std::for_each(rgbParams.begin(), rgbParams.end(), [&m] (double& x) {x += m;});

    return new modelRGB(rgbParams);
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
    double H = params[0];
    double L = params[1];
    double S = params[2];

    double C = (1 - abs(2*L - 1)) * S;
    double X = C * (1 - abs(fmod(H*6,2) - 1));

    QVector<double> rgbParams = modelRGB::rgbFromCXH(C,X,H);

    double m = L - C / 2;

    std::for_each(rgbParams.begin(), rgbParams.end(), [&m] (double& x) {x += m;});

    return new modelRGB(rgbParams);
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

