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
    static QString ColorModelName (int id);
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
    modelRGB* toRGB() override {
        return this;
    }
    modelCMYK* toCMYK () override;
    modelHSV* toHSV () override;
    modelHLS* toHLS () override;
    modelXYZ* toXYZ () override;
    modelLAB* toLAB () override;
//    QVector<QString> modelParamNames() override { return {"R","G","B"};};
private:
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
    modelRGB* toRGB() override;
    modelCMYK* toCMYK () override {
        return this;
    }
    modelHSV* toHSV () override;
    modelHLS* toHLS () override;
    modelXYZ* toXYZ () override;
    modelLAB* toLAB () override;
//    QVector<QString> modelParamNames() override { return {"C","M","Y","K"};};
private:
    double C,M,Y,K;
};

//class modelHSV : public colorModel {
//public:
//    modelHSV(double _H, double _S, double _V) {
//        H = _H;
//        S = _S;
//        V = _V;
//    }
//    modelRGB * toRGB() override;
//    modelCMYK* toCMYK () override;
//    modelHSV* toHSV () override;
//    modelHLS* toHLS () override;
//    modelXYZ* toXYZ () override;
//    modelLAB* toLAB () override;
////    QVector<QString> modelParamNames() override { return {"H","S","V"};};
//private:
//    double H,S,V;
//};

//class modelHLS : public colorModel {
//public:
//    modelHLS(double _H,double _L, double _S) {
//        H = _H;
//        L = _L;
//        S = _S;
//    }
//    modelRGB * toRGB() override;
//    modelCMYK* toCMYK () override;
//    modelHSV* toHSV () override;
//    modelHLS* toHLS () override;
//    modelXYZ* toXYZ () override;
//    modelLAB* toLAB () override;
////    QVector<QString> modelParamNames() override { return {"H","L","S"};};
//private:
//    double H,L,S;
//};

//class modelXYZ : public colorModel {
//public:
//    modelXYZ(double _X, double _Y, double _Z) {
//        X = _X;
//        Y = _Y;
//        Z = _Z;
//    }
//    modelRGB * toRGB() override;
//    modelCMYK* toCMYK () override;
//    modelHSV* toHSV () override;
//    modelHLS* toHLS () override;
//    modelXYZ* toXYZ () override;
//    modelLAB* toLAB () override;
////    QVector<QString> modelParamNames() override { return {"X","Y","Z"};};
//private:
//    double X,Y,Z;
//};

//class modelLAB : public colorModel {
//public:
//    modelLAB(double _L, double _A, double _B) {
//        L = _L;
//        A = _A;
//        B = _B;
//    }
//    modelRGB * toRGB() override;
//    modelCMYK* toCMYK () override;
//    modelHSV* toHSV () override;
//    modelHLS* toHLS () override;
//    modelXYZ* toXYZ () override;
//    modelLAB* toLAB () override;
////    QVector<QString> modelParamNames() override { return {"L","A","B"};};
//private:
//    double L,A,B;
//};



#endif // COLORMODEL_H
