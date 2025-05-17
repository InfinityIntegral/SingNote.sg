#ifndef SGPENSTROKESELECTORMANAGEMENT_H
#define SGPENSTROKESELECTORMANAGEMENT_H

#include <QObject>
#include "openglincludes.h"

class SGPenStrokeSelectorManagement : public QObject
{
    Q_OBJECT
public:
    static void startselector();
    static void resizeselector();
    static void activateselector();
    static void startmoveselector();
    static void ongoingmoveselector();
    static void endmoveselector();
    static void startresizeselector();
    static void ongoingresizeselector();
    static void endresizeselector();
    static void deleteselector();
    static void touchstart();
    static void touchongoing();
    static void touchend();
    static bool selectorexist;
    static float selectorx;
    static float selectory;
    static float selectorw;
    static float selectorh;
    static GLuint vao;
    static GLuint vbo;
    static GLuint ebo;
    static GLuint resizevao;
    static GLuint resizevbo;
    static GLuint resizeebo;
    static float initx;
    static float inity;
    static float inittouchx;
    static float inittouchy;
    static bool drawingtouchinselector();
    static int selectortouchmode;
private:
    SGPenStrokeSelectorManagement(){}
    ~SGPenStrokeSelectorManagement(){}
};

#endif // SGPENSTROKESELECTORMANAGEMENT_H
