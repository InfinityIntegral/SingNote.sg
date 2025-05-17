#ifndef SGCOLLIDERMANAGEMENT_H
#define SGCOLLIDERMANAGEMENT_H

#include <QObject>
#include "sgpolylinecollider.h"
#include "sgpenstrokeobject.h"
#include "sghighlighterstrokeobject.h"

class SGColliderManagement : public QObject
{
    Q_OBJECT
public:
    static SGPolylineCollider* penstrokegetcollider(SGPenStrokeObject* x);
    static SGPolylineCollider* highlighterstrokegetcollider(SGHighlighterStrokeObject* x);
    static void registercollider(SGCollider* x, int type, int& rangeidx, int& idx);
    static QVector<SGPolylineCollider*>* circleintersectpenstroke(float x, float y, float r);
    static QVector<SGPolylineCollider*>* circleintersecthighlighterstroke(float x, float y, float r);
    static void circleintersectpenstrokecolliderrange(float x, float y, float r, int ri, QVector<SGPolylineCollider*>* o);
    static void circleintersecthighlighterstrokecolliderrange(float x, float y, float r, int ri, QVector<SGPolylineCollider*>* o);
    static bool circleintersectpolylinecollider(float x, float y, float r, SGPolylineCollider* c);
    static bool circleintersect3points(float x, float y, float r, float x1, float y1, float x2, float y2, float x3, float y3, float w);
    static bool circleintersect2points(float x, float y, float r, float x1, float y1, float x2, float y2, float w);

private:
    SGColliderManagement(){}
    ~SGColliderManagement(){}
};

#endif // SGCOLLIDERMANAGEMENT_H
