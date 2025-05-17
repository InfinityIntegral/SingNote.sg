#ifndef SGFILETYPEENUM_H
#define SGFILETYPEENUM_H

#include <QObject>

class SGFileTypeEnum : public QObject
{
    Q_OBJECT
public:
    static int Note;
    static int StickerPack;

private:
    SGFileTypeEnum(){}
    ~SGFileTypeEnum(){}
};

#endif // SGFILETYPEENUM_H
