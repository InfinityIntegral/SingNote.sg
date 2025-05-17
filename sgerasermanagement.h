#ifndef SGERASERMANAGEMENT_H
#define SGERASERMANAGEMENT_H

#include <QObject>
#include "openglincludes.h"
#include "sgpenstrokeobject.h"
#include "sghighlighterstrokeobject.h"

class SGEraserManagement : public QObject
{
    Q_OBJECT
public:
    static void createeraser();
    static void moveeraser();
    static void deleteeraser();
    static float posx;
    static float posy;
    static GLuint vao;
    static GLuint vbo;
    static GLuint ebo;
    static void erasepenstroke(SGPenStrokeObject* x);
    static void erasehighlighterstroke(SGHighlighterStrokeObject* x);
    static void generatepartialpenstrokes(SGPenStrokeObject* o, float x, float y, float r);
    static void generatepartialhighlighterstrokes(SGHighlighterStrokeObject* o, float x, float y, float r);

private:
    SGEraserManagement(){}
    ~SGEraserManagement(){}
};

#endif // SGERASERMANAGEMENT_H
