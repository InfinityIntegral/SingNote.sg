#ifndef SGCOLLIDER_H
#define SGCOLLIDER_H

#include "sgnoteobject.h"
#include "sgpermanentobject.h"

class SGCollider : public SGNoteObject
{
public:
    SGCollider();
    ~SGCollider();
    float l;
    float r;
    float u;
    float d;
    SGPermanentObject* obj;
};

#endif // SGCOLLIDER_H
