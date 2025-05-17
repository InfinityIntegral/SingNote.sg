#ifndef SGPENSTROKEOBJECT_H
#define SGPENSTROKEOBJECT_H

#include "sgpolylineobject.h"
#include <QVector>

class SGPenStrokeObject : public SGPolylineObject
{
public:
    SGPenStrokeObject(QUuid guid, float x, float y, float w, uint c, int z);
    ~SGPenStrokeObject();
    QVector<float>* pointsx;
    QVector<float>* pointsy;
};

#endif // SGPENSTROKEOBJECT_H
