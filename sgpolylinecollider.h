#ifndef SGPOLYLINECOLLIDER_H
#define SGPOLYLINECOLLIDER_H

#include "sgcollider.h"
#include <QVector>

class SGPolylineCollider : public SGCollider
{
public:
    SGPolylineCollider();
    ~SGPolylineCollider();
    bool pointsshared;
    float originx;
    float originy;
    float w;
    QVector<float>* pointsx;
    QVector<float>* pointsy;
};

#endif // SGPOLYLINECOLLIDER_H
