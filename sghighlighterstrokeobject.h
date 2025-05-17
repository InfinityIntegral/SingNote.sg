#ifndef SGHIGHLIGHTERSTROKEOBJECT_H
#define SGHIGHLIGHTERSTROKEOBJECT_H

#include "sgpolylineobject.h"
#include <QVector>

class SGHighlighterStrokeObject : public SGPolylineObject
{
public:
    SGHighlighterStrokeObject(QUuid guid, float x, float y, float w, uint c, int z);
    ~SGHighlighterStrokeObject();
    QVector<float>* pointsx;
    QVector<float>* pointsy;
};

#endif // SGHIGHLIGHTERSTROKEOBJECT_H
