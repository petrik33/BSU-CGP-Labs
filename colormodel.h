#ifndef COLORMODEL_H
#define COLORMODEL_H

#include <QVector>
#include <QtMath>
#include <QMessageBox>
#include <QObject>

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

class colorModel : public QObject
{
    Q_OBJECT
public:
    colorModel();
    virtual ~colorModel() {};
    virtual modelRGB* toRGB() = 0;
    virtual modelCMYK* toCMYK() = 0;
    virtual modelHSV* toHSV() = 0;
    virtual modelHLS* toHLS() = 0;
    virtual modelXYZ* toXYZ() = 0;
    virtual modelLAB* toLAB() = 0;
    static QString ColorModelName(int id);
    static colorModel* makeColorModel(COLOR_MODEL modelID);
    colorModel* convertColorModel(COLOR_MODEL modelID);
//    virtual QVector<QString> modelParamNames() = 0;
    double* getParams() {
        return params;
    }
public slots:
    void setParams(double* newParams);
protected:
    double params[4];
};

class modelRGB : public colorModel {
public:
    modelRGB(double _R,double _G,double _B) {
        params[0] = _R;
        params[1] = _G;
        params[2] = _B;
    }
    modelRGB() {
        params[0] = 0;
        params[1] = 0;
        params[2] = 0;
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
//    double R,G,B;
};

class modelCMYK : public colorModel {
public:
    modelCMYK(double _C,double _M, double _Y,double _K) {
        params[0] = _C;
        params[1] = _M;
        params[2] = _Y;
        params[3] = _K;
    }
    modelCMYK() {
        params[0] = 0;
        params[1] = 0;
        params[2] = 0;
        params[3] = 1;
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
//    double C,M,Y,K;
};

class modelHSV : public colorModel {
public:
    modelHSV(double _H, double _S, double _V) {
        params[0] = _H;
        params[1] = _S;
        params[2] = _V;
    }
    modelHSV() {
        params[0] = 0;
        params[1] = 0;
        params[2] = 0;
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
//    double H,S,V;
};

class modelHLS : public colorModel {
public:
    modelHLS(double _H,double _L, double _S) {
        params[0] = _H;
        params[1] = _L;
        params[2] = _S;
    };
    modelHLS() {
        params[0] = 0;
        params[1] = 0;
        params[2] = 0;
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
//    double H,L,S;
};

class modelXYZ : public colorModel {
public:
    modelXYZ(double _X, double _Y, double _Z) {
        params[0] = _X;
        params[1] = _Y;
        params[2] = _Z;
    }
    modelXYZ() {
        params[0] = 0;
        params[1] = 0;
        params[2] = 0;
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
//    double X,Y,Z;
};

class modelLAB : public colorModel {
public:
    modelLAB(double _L, double _A, double _B) {
        params[0] = _L;
        params[1] = _A;
        params[2] = _B;
    };
    modelLAB() {
        params[0] = 0;
        params[1] = 0;
        params[2] = 0;
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
//    double L,A,B;
};


#endif // COLORMODEL_H
