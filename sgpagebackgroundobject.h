#ifndef SGPAGEBACKGROUNDOBJECT_H
#define SGPAGEBACKGROUNDOBJECT_H

#include "sgpermanentobject.h"
#include "sgnotebackgroundrenderer.h"

class SGPageBackgroundObject : public SGPermanentObject
{
public:
    SGPageBackgroundObject(int pn, QUuid guid);
    ~SGPageBackgroundObject();
    int pagenumber;
};

#endif // SGPAGEBACKGROUNDOBJECT_H
