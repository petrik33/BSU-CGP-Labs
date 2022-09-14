#ifndef COLORMODEL_H
#define COLORMODEL_H

#include <QVector>
#include <QtMath>

class modelRGB;
class modelCMYK;
class modelHSV;
class modelHLS;
class modelXYZ;
class modelLAB;

const QVector<QVector<QString>> colorModelsParamNames = {
    {"R","G","B"},
    {"C","M","Y","K"},
    {"H","S","V"},
    {"H","L","S"},
    {"X","Y","Z"},
    {"L","A","B"}
};

const QVector<QVector<QVector<int>>> colorModelsParamRange = {
    {{0,255},{0,255},{0,255}},
    {{0,100},{0,100},{0,100},{0,100}},
    {{0,360},{0,100},{0,100}},
    {{0,360},{0,100},{0,100}},
    {{0,95},{0,100},{0,108}},
    {{0,100},{-128,127},{-128,127}}
};

const int colorModelsMaxParams = 4;//Manually Counted (it's not perfect but I'm lazy to code automatic count)

enum COLOR_MODEL {
    RGB = 0,
    CMYK,
    HSV,
    HLS,
    XYZ,
    LAB,
    MODELS_NUMBER
};

class colorModel
{
public:
    colorModel();
    virtual modelRGB* toRGB() = 0;
    virtual modelCMYK* toCMYK() = 0;
    virtual modelHSV* toHSV() = 0;
    virtual modelHLS* toHLS() = 0;
    virtual modelXYZ* toXYZ() = 0;
    virtual modelLAB* toLAB() = 0;
//    virtual QVector<QString> modelParamNames() = 0;
protected:
};

class modelRGB : public colorModel {
public:
    modelRGB(double _R,double _G,double _B) {
        R = _R;
        G = _G;
        B = _B;
    }
    modelRGB() {
        R = 0;
        G = 0;
        B = 0;
    }
    modelRGB* toRGB() override {
        return this;
    }
    modelCMYK* toCMYK () override;
    modelHSV* toHSV () override;
    modelHLS* toHLS () override;
    modelXYZ* toXYZ () override;
    modelLAB* toLAB () override;
//    QVector<QString> modelParamNames() override { return {"R","G","B"};};
    double R,G,B;
};

class modelCMYK : public colorModel {
public:
    modelCMYK(double _C,double _M, double _Y,double _K) {
        C = _C;
        M = _M;
        Y = _Y;
        K = _K;
    }
    modelCMYK() {
        C = 0;
        M = 0;
        Y = 0;
        K = 1;
    }
    modelRGB* toRGB() override;
    modelCMYK* toCMYK () override {
        return this;
    }
    modelHSV* toHSV () override;
    modelHLS* toHLS () override;
    modelXYZ* toXYZ () override;
    modelLAB* toLAB () override;
//    QVector<QString> modelParamNames() override { return {"C","M","Y","K"};};
    double C,M,Y,K;
};

class modelHSV : public colorModel {
public:
    modelHSV(double _H, double _S, double _V) {
        H = _H;
        S = _S;
        V = _V;
    }
    modelHSV() {
        H = 0;
        S = 0;
        V = 0;
    }
    modelRGB * toRGB() override;
    modelCMYK* toCMYK () override;
    modelHSV* toHSV () override {
        return this;
    };
    modelHLS* toHLS () override;
    modelXYZ* toXYZ () override;
    modelLAB* toLAB () override;
//    QVector<QString> modelParamNames() override { return {"H","S","V"};};
    double H,S,V;
};

class modelHLS : public colorModel {
public:
    modelHLS(double _H,double _L, double _S) {
        H = _H;
        L = _L;
        S = _S;
    };
    modelHLS() {
        H = 0;
        L = 0;
        S = 0;
    };
    modelRGB * toRGB() override;
    modelCMYK* toCMYK () override;
    modelHSV* toHSV () override;
    modelHLS* toHLS () override {
        return this;
    };
    modelXYZ* toXYZ () override;
    modelLAB* toLAB () override;
//    QVector<QString> modelParamNames() override { return {"H","L","S"};};
    double H,L,S;
};

class modelXYZ : public colorModel {
public:
    modelXYZ(double _X, double _Y, double _Z) {
        X = _X;
        Y = _Y;
        Z = _Z;
    }
    modelXYZ() {
        X = 0;
        Y = 0;
        Z = 0;
    };
    modelRGB * toRGB() override;
    modelCMYK* toCMYK () override;
    modelHSV* toHSV () override;
    modelHLS* toHLS () override;
    modelXYZ* toXYZ () override {
        return this;
    };
    modelLAB* toLAB () override;
//    QVector<QString> modelParamNames() override { return {"X","Y","Z"};};
    double X,Y,Z;
};

class modelLAB : public colorModel {
public:
    modelLAB(double _L, double _A, double _B) {
        L = _L;
        A = _A;
        B = _B;
    };
    modelLAB() {
        L = 0;
        A = 0;
        B = 0;
    };
    modelRGB * toRGB() override;
    modelCMYK* toCMYK () override;
    modelHSV* toHSV () override;
    modelHLS* toHLS () override;
    modelXYZ* toXYZ () override;
    modelLAB* toLAB () override {
        return this;
    };
//    QVector<QString> modelParamNames() override { return {"L","A","B"};};
    double L,A,B;
};

colorModel* makeColorModel(COLOR_MODEL id) {
    switch (id) {
    case COLOR_MODEL::RGB:
        break;
    case COLOR_MODEL::CMYK:
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
    }
}



#endif // COLORMODEL_H
