#ifndef SGNOTEQUICKMOVEMANAGEMENT_H
#define SGNOTEQUICKMOVEMANAGEMENT_H

#include <QObject>
#include <QTimer>

class SGNoteQuickMoveManagement : public QObject
{
    Q_OBJECT
public:
    static QTimer* quickmovetimer;
    static float startposx;
    static float startposy;
    static float startzoom;
    static void applyquickmove();
    static int n;

private:
    SGNoteQuickMoveManagement(){}
    ~SGNoteQuickMoveManagement(){}
};

#endif // SGNOTEQUICKMOVEMANAGEMENT_H
