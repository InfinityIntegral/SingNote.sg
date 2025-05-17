#ifndef SGNOTESAVINGMANAGEMENT_H
#define SGNOTESAVINGMANAGEMENT_H

#include <QObject>
#include "sgpagebackgroundobject.h"
#include "sgpenstrokeobject.h"
#include "sghighlighterstrokeobject.h"

class SGNoteSavingManagement : public QObject
{
    Q_OBJECT
public:
    static void opennote(QString path);
    static void savenote(QString path);
    static void initialiserenderpagebackground(SGPageBackgroundObject* x);
    static void initialiserenderpenstroke(SGPenStrokeObject* x);
    static void initialiserenderhighlighterstroke(SGHighlighterStrokeObject* x);
    static void initialisepenstroke(SGPenStrokeObject* x);
    static void initialisehighlighterstroke(SGHighlighterStrokeObject* x);

private:
    SGNoteSavingManagement(){}
    ~SGNoteSavingManagement(){}
};

#endif // SGNOTESAVINGMANAGEMENT_H
