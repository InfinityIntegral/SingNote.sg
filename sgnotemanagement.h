#ifndef SGNOTEMANAGEMENT_H
#define SGNOTEMANAGEMENT_H

#include <QObject>
#include "sgrenderingrange.h"
#include "sgcolliderrange.h"

class SGNoteManagement : public QObject
{
    Q_OBJECT
public:
    static bool noteisopen;
    static QVector<SGPermanentObject*>* notedata;
    static QHash<int, SGRenderingRange*>* renderingdata;
    static QHash<int, SGColliderRange*>* collidersdata;
    static int penstrokezindex;
    static int highlighterstrokezindex;

private:
    SGNoteManagement(){}
    ~SGNoteManagement(){}
};

#endif // SGNOTEMANAGEMENT_H
