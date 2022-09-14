#ifndef CustomColorPalette_H
#define CustomColorPalette_H

#include <QWidget>
#include <QGridLayout>

#include <QPushButton>

#include <QPainter>
#include <QRandomGenerator>
#include <QTime>

#include <QVector>
#include <QColor>

#include <QMessageBox>

#include "palettebutton.h"

class CustomColorPalette : public QWidget
{
    Q_OBJECT
public:
    explicit CustomColorPalette(int w, int h,QWidget *parent = nullptr);

signals:
    void colorPicked(QColor color);
public slots:
    bool setPaletteWidth(int w) {
        if(w * paletteH > maxColors) return false;
        paletteW = w;
        return true;
    };
    bool setPaletteHeight(int h) {
        if(paletteW * h > maxColors) return false;
        paletteH = h;
        return true;
    };
    bool setPaletteDimensions(int w,int h) {
        if(w * h > maxColors) return false;
        paletteW = w;
        paletteH = h;
        updateColors();
        return true;
    };
protected slots:
    bool updateColors();
    void colorPressed(QColor color);
protected:
    QPushButton* paletteButtonCreate(QColor color);
    QRandomGenerator random;
    QGridLayout* bLayout = nullptr;
    int paletteW = 0;
    int paletteH = 0;
//    void paintEvent(QPaintEvent *event) override;
    QVector<QColor> colorsUsed;
    QVector<QColor> colorsAvailable = {
        QColor("aliceblue"),
        QColor("antiquewhite"),
        QColor("aqua"),
        QColor("aquamarine"),
        QColor("azure"),
        QColor("beige"),
        QColor("bisque"),
        QColor("black"),
        QColor("blanchedalmond"),
        QColor("blue"),
        QColor("blueviolet"),
        QColor("brown"),
        QColor("burlywood"),
        QColor("cadetblue"),
        QColor("chartreuse"),
        QColor("chocolate"),
        QColor("coral"),
        QColor("cornflowerblue"),
        QColor("cornsilk"),
        QColor("crimson"),
        QColor("cyan"),
        QColor("darkblue"),
        QColor("darkcyan"),
        QColor("darkgoldenrod"),
        QColor("darkgray"),
        QColor("darkgreen"),
        QColor("darkgrey"),
        QColor("darkkhaki"),
        QColor("darkmagenta"),
        QColor("darkolivegreen"),
        QColor("darkorange"),
        QColor("darkorchid"),
        QColor("darkred"),
        QColor("darksalmon"),
        QColor("darkseagreen"),
        QColor("darkslateblue"),
        QColor("darkslategray"),
        QColor("darkslategrey"),
        QColor("darkturquoise"),
        QColor("darkviolet"),
        QColor("deeppink"),
        QColor("deepskyblue"),
        QColor("dimgray"),
        QColor("dimgrey"),
        QColor("dodgerblue"),
        QColor("firebrick"),
        QColor("floralwhite"),
        QColor("forestgreen"),
        QColor("fuchsia"),
        QColor("gainsboro"),
        QColor("ghostwhite"),
        QColor("gold"),
        QColor("goldenrod"),
        QColor("gray"),
        QColor("green"),
        QColor("greenyellow"),
        QColor("honeydew"),
        QColor("hotpink"),
        QColor("indianred"),
        QColor("indigo"),
        QColor("ivory"),
        QColor("khaki"),
        QColor("lavender"),
        QColor("lavenderblush"),
        QColor("lawngreen"),
        QColor("lemonchiffon"),
        QColor("lightblue"),
        QColor("lightcoral"),
        QColor("lightcyan"),
        QColor("lightgoldenrodyello"),
        QColor("lightgray"),
        QColor("lightgreen"),
        QColor("lightgrey"),
        QColor("lightpink"),
        QColor("lightsalmon"),
        QColor("lightseagreen"),
        QColor("lightskyblue"),
        QColor("lightslategray"),
        QColor("lightslategrey"),
        QColor("lightsteelblue"),
        QColor("lightyellow"),
        QColor("lime"),
        QColor("limegreen"),
        QColor("linen"),
        QColor("magenta"),
        QColor("maroon"),
        QColor("mediumaquamarine"),
        QColor("mediumblue"),
        QColor("mediumorchid"),
        QColor("mediumpurple"),
        QColor("mediumseagreen"),
        QColor("mediumslateblue"),
        QColor("mediumspringgreen"),
        QColor("mediumturquoise"),
        QColor("mediumvioletred"),
        QColor("midnightblue"),
        QColor("mintcream"),
        QColor("mistyrose"),
        QColor("moccasin"),
        QColor("navajowhite"),
        QColor("navy"),
        QColor("oldlace"),
        QColor("olive"),
        QColor("olivedrab"),
        QColor("orange"),
        QColor("orangered"),
        QColor("orchid"),
        QColor("palegoldenrod"),
        QColor("palegreen"),
        QColor("paleturquoise"),
        QColor("palevioletred"),
        QColor("papayawhip"),
        QColor("peachpuff"),
        QColor("peru"),
        QColor("pink"),
        QColor("plum"),
        QColor("powderblue"),
        QColor("purple"),
        QColor("red"),
        QColor("rosybrown"),
        QColor("royalblue"),
        QColor("saddlebrown"),
        QColor("salmon"),
        QColor("sandybrown"),
        QColor("seagreen"),
        QColor("seashell"),
        QColor("sienna"),
        QColor("silver"),
        QColor("skyblue"),
        QColor("slateblue"),
        QColor("slategray"),
        QColor("slategrey"),
        QColor("snow"),
        QColor("springgreen"),
        QColor("steelblue"),
        QColor("tan"),
        QColor("teal"),
        QColor("thistle"),
        QColor("tomato"),
        QColor("turquoise"),
        QColor("violet"),
        QColor("wheat"),
        QColor("white"),
        QColor("whitesmoke"),
        QColor("yellow"),
        QColor("yellowgreen")
    };
    const int maxColors = colorsAvailable.length();
};

#endif // CustomColorPalette_H
