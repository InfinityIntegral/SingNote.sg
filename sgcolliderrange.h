#ifndef SGCOLLIDERRANGE_H
#define SGCOLLIDERRANGE_H

#include "sgnoteobject.h"
#include "sgpolylinecollider.h"

class SGColliderRange : public SGNoteObject
{
public:
    SGColliderRange(int type, int y);
    ~SGColliderRange();
    float startpage;
    int type;
    int y;
    QVector<SGPolylineCollider*>* penstrokes;
    QVector<SGPolylineCollider*>* highlighterstrokes;
};

/*
1-15: w = 1/8
16-22: w = 1/4
23-25: w = 1/2
26: w = 1
27: w = 2
28: else
*/

#endif // SGCOLLIDERRANGE_H
