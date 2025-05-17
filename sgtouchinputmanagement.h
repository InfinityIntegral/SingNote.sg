#ifndef SGTOUCHINPUTMANAGEMENT_H
#define SGTOUCHINPUTMANAGEMENT_H

#include <QObject>
#include <QTouchEvent>
#include "sgtouchevent.h"

class SGTouchInputManagement : public QObject
{
    Q_OBJECT
public:
    static void processtouchfromqt(QTouchEvent* e);
    static bool scheduled;
    static QVector<SGTouchEvent>* activetouches;
    static void processtouchevents();
    static SGTouchEvent drawingtouch;
    static SGTouchEvent scrolltouch1;
    static SGTouchEvent scrolltouch2;
    static SGTouchEvent selecttouch;
    static void drawstart();
    static void drawongoing();
    static void drawend();
    static void scroll1start();
    static void scroll1ongoing();
    static void scroll1end();
    static void scroll2start();
    static void scroll2ongoing();
    static void scroll2end();
    static void selectstart();
    static void selectongoing();
    static void selectend();
    static int quickmovemode;
    static float quickmovex;
    static float quickmovey;
    static QElapsedTimer* quickmovetimer;
    static void quickmovestart();
    static void quickmoveongoing();
    static void quickmoveend();

private:
    SGTouchInputManagement(){}
    ~SGTouchInputManagement(){}
};

#endif // SGTOUCHINPUTMANAGEMENT_H
