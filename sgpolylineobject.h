#ifndef SGPOLYLINEOBJECT_H
#define SGPOLYLINEOBJECT_H

#include "sgpermanentobject.h"

class SGPolylineObject : public SGPermanentObject
{
public:
    SGPolylineObject(QUuid guid, float x, float y, float w, uint c, int z);
    float originx;
    float originy;
    float width;
    uint colour;
    int zdepth;
    int renderrangeindex;
    int renderkey;
    int ebostartindex;
    int ebolength;
};

#endif // SGPOLYLINEOBJECT_H
