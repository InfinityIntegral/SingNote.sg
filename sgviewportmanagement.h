#ifndef SGVIEWPORTMANAGEMENT_H
#define SGVIEWPORTMANAGEMENT_H

#include <QObject>

class SGViewportManagement : public QObject
{
    Q_OBJECT
public:
    static float startfocusedposx;
    static float startfocusedposy;
    static float startfocusedzoom;
    static float startscroll1x;
    static float startscroll1y;
    static float startscroll2x;
    static float startscroll2y;

public slots:
    static void movestart();
    static void moveongoing();
    static void zoomstart();
    static void zoomongoing();

private:
    SGViewportManagement(){}
    ~SGViewportManagement(){}
};

#endif // SGVIEWPORTMANAGEMENT_H
