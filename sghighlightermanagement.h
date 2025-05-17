#ifndef SGHIGHLIGHTERMANAGEMENT_H
#define SGHIGHLIGHTERMANAGEMENT_H

#include <QObject>
#include "sghighlighterstrokeobject.h"
#include "openglincludes.h"

class SGHighlighterManagement : public QObject
{
    Q_OBJECT
public:
    static void startnewhighlighterstroke();
    static void addtonewhighlighterstroke();
    static void endnewhighlighterstroke();
    static SGHighlighterStrokeObject* activehighlighterstroke;
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
    SGHighlighterManagement(){}
    ~SGHighlighterManagement(){}
};

#endif // SGHIGHLIGHTERMANAGEMENT_H
