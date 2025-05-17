#ifndef SGPENMANAGEMENT_H
#define SGPENMANAGEMENT_H

#include <QObject>
#include "sgpenstrokeobject.h"
#include "sgnotepenstrokerenderer.h"

class SGPenManagement : public QObject
{
    Q_OBJECT
public:
    static void startnewpenstroke();
    static void addtonewpenstroke();
    static void endnewpenstroke();
    static SGPenStrokeObject* activepenstroke;
    static GLuint vbo;
    static int vbors;
    static int vboms;
    static GLuint ebo;
    static int ebors;
    static int eboms;
    static GLuint vao;
    static int maxp;
    static int minp;

private:
    SGPenManagement(){}
    ~SGPenManagement(){}
};

#endif // SGPENMANAGEMENT_H
