#ifndef SGGENERALLIBRARY_H
#define SGGENERALLIBRARY_H

#include <QObject>
#include <QWidget>
#include <QUuid>
#include "openglincludes.h"

class SGGeneralLibrary : public QObject
{
    Q_OBJECT
public:
    static QFont* SingScriptSG;
    static void SetUIStyle(QWidget* obj, QString& k, QString& v);
    static QString stylesheetfieldbackgroundcolour;
    static QString stylesheetfieldtextcolour;
    static QString stylesheetfieldfontsize;
    static QString stylesheetfieldborder;
    static QString stylesheetfieldselectedtextcolour;
    static QString stylesheetfieldselectedbackgroundcolour;
    static QString stylesheetfieldscrollbarwidth;
    static QString stylesheetnoborder;
    static void updatefontsize(QWidget* obj);
    static QString StringToNCL256(QString& s);
    static QString NCL256ToString(QString& s);
    static void setscrollviewstylesheet(QWidget* obj);
    static void updatescrollbarwidth(QWidget* obj);
    static QString* getwrappedtext(QString s);
    static QString ColourUintToCSS(uint c);
    static float DrawingTouchToNoteCoordsX();
    static float DrawingTouchToNoteCoordsY();
    static QUuid GetNewGUID();
    static void rotateplus90(float x, float y, float& newx, float& newy);
    static void normalisevector(float x, float y, float& newx, float& newy);
    static void doublevbo(QOpenGLFunctions_4_5_Core* glc, GLuint& vbo, int& ms);
    static void doubleebo(QOpenGLFunctions_4_5_Core* glc, GLuint& ebo, int& ms);
    static int getrenderingdataindex(int a, int b);
    static uint ColourCSSToUint(QString& s);
    static float plusinf;
    static float minusinf;
    static int getcolliderdataindex(int x, int y);
    static float getdetsignonly(float x1, float y1, float x2, float y2, float x3, float y3);

private:
    SGGeneralLibrary(){}
    ~SGGeneralLibrary(){}
};

#endif // SGGENERALLIBRARY_H
