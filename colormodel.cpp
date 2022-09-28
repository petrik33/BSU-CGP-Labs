#include "colormodel.h"
#include <QDebug>

//Color Model General

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

double colorModel::paramNormalize(double value, COLOR_MODEL modelID, int paramID)
{
    double lRange = colorModelsParamRange[int(modelID)][paramID][0];
    double rRange = colorModelsParamRange[int(modelID)][paramID][1];
    double normalizedValue = (value - lRange) / (rRange - lRange);
    return normalizedValue;
}

double colorModel::paramEvaluate(double value, COLOR_MODEL modelID, int paramID)
{
    double lRange = colorModelsParamRange[int(modelID)][paramID][0];
    double rRange = colorModelsParamRange[int(modelID)][paramID][1];
    double evaluatedValue = lRange + value * (rRange - lRange);
    return evaluatedValue;
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

//RGB

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
    QVector<double> paramsCopy = params;

    auto func = [](double &x){
        if(x >= 0.04045) {
            x = pow((x+0.055) / (1.055),2.4);
            return;
        }
        x /= 12.92;
    };
    std::for_each(paramsCopy.begin(),paramsCopy.end()-1,func);

    QGenericMatrix<1, 3, double> rgbMatrix;
    for(int i = 0; i < 3; i++) {
        rgbMatrix(i,0) = paramsCopy[i];
    }

    double conversionNumbers[] = {
        0.4124564,  0.3575761,  0.1804375,
        0.2126729,  0.7151522,  0.0721750,
        0.0193339,  0.1191920,  0.9503041
    };

    QGenericMatrix<3,3, double> cMatrix(conversionNumbers);
    QGenericMatrix<1, 3, double> xyzMatrix = cMatrix * rgbMatrix;
    double x = xyzMatrix(0,0);
    double y = xyzMatrix(1,0);
    double z = xyzMatrix(2,0);

    return new modelXYZ(x,y,z);
}

modelLAB *modelRGB::toLAB()
{
    modelXYZ* transit = toXYZ();
    return transit->toLAB();
}

//CMYK

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
    modelRGB* subModel = toRGB();
    return subModel->toHSV();
}

modelHLS *modelCMYK::toHLS()
{
    modelRGB* subModel = toRGB();
    return subModel->toHLS();
}

modelXYZ *modelCMYK::toXYZ()
{
    modelRGB* subModel = toRGB();
    return subModel->toXYZ();
}

modelLAB *modelCMYK::toLAB()
{
    return toRGB()->toLAB();
}

//HSV

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
    modelRGB* subModel = toRGB();
    return subModel->toCMYK();
}

modelHLS *modelHSV::toHLS()
{
    double H = params[0];
    double Sv = params[1];
    double V = params[2];

    double L = V * (1 - Sv/2);
    double Sl = (L == 1 || L == 0) ? 0 : (V - L) / qMin(L, 1 - L);

    return new modelHLS(H,L,Sl);
}

modelXYZ *modelHSV::toXYZ()
{
    modelRGB* transit = toRGB();
    return transit->toXYZ();
}

modelLAB *modelHSV::toLAB()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelLAB();
}

//HLS

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
    modelRGB* subModel = toRGB();
    return subModel->toCMYK();
}

modelHSV *modelHLS::toHSV()
{
    double H = params[0];
    double L = params[1];
    double Sl = params[2];

    double V = L + Sl * qMin(L,1-L);
    double Sv = (V == 0) ? 0 : 2 * (1 - L / V);
    return new modelHSV(H,Sv,V);
}

modelXYZ *modelHLS::toXYZ()
{
    modelRGB* transit = toRGB();
    return transit->toXYZ();
}

modelLAB *modelHLS::toLAB()
{
    QMessageBox::information(nullptr,"To Do","Sorry, this type of convertion isn't supported yet"); //To do
    return new modelLAB();
}

//XYZ

modelRGB* modelXYZ::toRGB()
{
    QVector<double> paramsCopy = params;

    QGenericMatrix<1, 3, double> xyzMatrix;
    for(int i = 0; i < 3; i++) {
        xyzMatrix(i,0) = paramsCopy[i];
    }

    double conversionNumbers[] = {
        3.2404542, -1.5371385, -0.4985314,
       -0.9692660,  1.8760108,  0.0415560,
        0.0556434, -0.2040259,  1.0572252,
    };

    QGenericMatrix<3, 3, double> cMatrix(conversionNumbers);
    QGenericMatrix<1, 3, double> rgbMatrix = cMatrix * xyzMatrix;

    bool inaccurate = false;

    QVector<double> rgbParams(colorModelsMaxParams,0);
    for(int i = 0; i < 3; i++) {
        double param = rgbMatrix(i,0);
        if(param < 0) {
            param = 0;
            inaccurate = true;
        }
        if(param > 1) {
            param = 1;
            inaccurate = true;
        }
        rgbParams[i] = param;
    }

    auto func = [](double &x){
        if(x >= 0.031308) {
            x = (1.055 * pow(x,1/2.4) - 0.055);
            return;
        }
        x *= 12.92;
    };

    emit inaccurateConversion(inaccurate);

    std::for_each(rgbParams.begin(),rgbParams.end()-1,func);

    return new modelRGB(rgbParams);
}

modelCMYK* modelXYZ::toCMYK()
{
    modelRGB* transit = toRGB();
    return transit->toCMYK();
}

modelHSV *modelXYZ::toHSV()
{
    modelRGB* transit = toRGB();
    return transit->toHSV();
}

modelHLS *modelXYZ::toHLS()
{
    modelRGB* transit = toRGB();
    return transit->toHLS();
}

modelLAB *modelXYZ::toLAB()
{
    QVector<double> paramsCopy = params;

    auto func = [](double &x){
        if(x >= 0.008856) {
            x = pow(x,1.0/3.0);
            return;
        }
        x = x * 7.787 + 16.0/116.0;
    };

    std::for_each(paramsCopy.begin(), paramsCopy.end() - 1, func);

    double x = paramsCopy[0];
    double y = paramsCopy[1];
    double z = paramsCopy[2];

    double L = paramNormalize(116.0 * y - 16.0, COLOR_MODEL::LAB, 0);
    double a = paramNormalize(500.0 * (x - y), COLOR_MODEL::LAB, 1);
    double b = paramNormalize(200.0 * (y - z), COLOR_MODEL::LAB, 2);

//    double whitePoint[] = {
//        95.047, 100, 108.883,
//    };
    return new modelLAB(L, a, b);
}

//LAB

modelRGB* modelLAB::toRGB()
{
    modelXYZ* transit = toXYZ();
    return transit->toRGB();
}

modelCMYK* modelLAB::toCMYK()
{
    return toRGB()->toCMYK();
}

modelHSV *modelLAB::toHSV()
{
    return toRGB()->toHSV();
}

modelHLS *modelLAB::toHLS()
{
    return toRGB()->toHLS();
}

modelXYZ *modelLAB::toXYZ()
{
    double L = params[0];
    double a = params[1];
    double b = params[2];

    auto func = [](double &x){
        if(x*x*x >= 0.008856) {
            x = pow(x,3);
            return;
        }
        x = (x - double(16/116)) * 7.787;
    };

    QVector<double> xyzParams(colorModelsMaxParams,0);
    L = paramEvaluate(L, COLOR_MODEL::LAB, 0);
    a = paramEvaluate(a, COLOR_MODEL::LAB, 1);
    b = paramEvaluate(b, COLOR_MODEL::LAB, 2);
    xyzParams[0] = (L + 16) / 116;
    xyzParams[1] = (a/500 + (L+16)/116);
    xyzParams[2] = (L+16) / 116 - b/200;
    std::for_each(xyzParams.begin(), xyzParams.end() - 1, func);
    return new modelXYZ(xyzParams);
}

