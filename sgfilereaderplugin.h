#ifndef SGFILEREADERPLUGIN_H
#define SGFILEREADERPLUGIN_H

#include <QObject>
#include <QFile>
#include <QDataStream>
#include <QUuid>

class SGFileReaderPlugin : public QObject
{
    Q_OBJECT
public:
    SGFileReaderPlugin(QString path);
    ~SGFileReaderPlugin();
    QFile* f;
    QDataStream* s;
    bool EndOfStream();
    bool ReadBool();
    int ReadInt();
    uint ReadUint();
    float ReadFloat();
    QByteArray ReadString(int l);
    QUuid ReadGUID();
};

#endif // SGFILEREADERPLUGIN_H
