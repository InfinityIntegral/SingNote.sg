#ifndef SGCENTRALMANAGEMENT_H
#define SGCENTRALMANAGEMENT_H

#include <QObject>
#include "sgrootwindow.h"
#include "sgsignalsemitter.h"
#include "sgwidget000451103.h"

class SGCentralManagement : public QObject
{
    Q_OBJECT
public:
    static QString colour0;
    static QString colour1;
    static QString colour2;
    static QString colour3;
    static float screenw;
    static float screenh;
    static float renderw;
    static float renderh;
    static float sizeunit;
    static SGRootWindow* rootwindow;
    static SGSignalsEmitter* signalsemitter;
    static SGWidget000451103* mainbackground;
    static QFont* SingNoteIcons;
    static void initialise();
    static void terminate();
    static QVector<QString>* openfilepath;
    static QString rootfilepath;
    static QString mergedfilepath();
    static float focusedpositionx;
    static float focusedpositiony;
    static float focusedzoom;
    static float pagew;
    static float pageh;
    static float marginx;
    static float marginy;
    static int interactionmode;
    static int activetooltype;
    static uint activetoolcolour;
    static float activetoolwidth;
    static float writeprecision;

private:
    SGCentralManagement(){}
    ~SGCentralManagement(){}
};

#endif // SGCENTRALMANAGEMENT_H
