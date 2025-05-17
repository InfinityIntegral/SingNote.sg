#ifndef SGNOTEINTERACTIONMODEENUM_H
#define SGNOTEINTERACTIONMODEENUM_H

#include <QObject>

class SGNoteInteractionModeEnum : public QObject
{
    Q_OBJECT
public:
    static int Normal;
    static int ScrollOnly;
    static int DrawOnly;

private:
    SGNoteInteractionModeEnum(){}
    ~SGNoteInteractionModeEnum(){}
};

#endif // SGNOTEINTERACTIONMODEENUM_H
