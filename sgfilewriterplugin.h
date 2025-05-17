#ifndef SGFILEWRITERPLUGIN_H
#define SGFILEWRITERPLUGIN_H

#include <QObject>
#include <QFile>
#include <QDataStream>
#include <QUuid>

class SGFileWriterPlugin : public QObject
{
    Q_OBJECT
public:
    SGFileWriterPlugin(QString path);
    ~SGFileWriterPlugin();
    QFile* f;
    QDataStream* s;
    void WriteBool(bool x);
    void WriteInt(int x);
    void WriteUint(uint x);
    void WriteFloat(float x);
    void WriteString(QByteArray& x);
    void WriteGUID(QUuid x);
signals:
};

#endif // SGFILEWRITERPLUGIN_H
