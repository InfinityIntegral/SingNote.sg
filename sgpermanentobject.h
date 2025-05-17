#ifndef SGPERMANENTOBJECT_H
#define SGPERMANENTOBJECT_H

#include "sgnoteobject.h"
#include <QUuid>

class SGPermanentObject : public SGNoteObject
{
public:
    SGPermanentObject(QUuid guid);
    QUuid guid;
    int type;
    int colliderrangeindex;
    int colliderindex;
    int dataindex;
};

#endif // SGPERMANENTOBJECT_H
