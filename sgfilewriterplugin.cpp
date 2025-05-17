#include "sgfilewriterplugin.h"

SGFileWriterPlugin::SGFileWriterPlugin(QString path){
    (*this).f = new QFile(path);
    (*(*this).f).open(QIODevice::Append | QIODevice::WriteOnly);
    (*this).s = new QDataStream((*this).f);
}

SGFileWriterPlugin::~SGFileWriterPlugin(){
    (*(*this).f).close();
    delete (*this).s;
    delete (*this).f;
}

void SGFileWriterPlugin::WriteBool(bool x){
    (*(*this).s) << x;
}

void SGFileWriterPlugin::WriteInt(int x){
    (*(*this).s) << x;
}

void SGFileWriterPlugin::WriteUint(uint x){
    (*(*this).s) << x;
}

void SGFileWriterPlugin::WriteFloat(float x){
    (*(*this).s) << x;
}

void SGFileWriterPlugin::WriteString(QByteArray& x){
    (*(*this).s).writeRawData(x.constData(), x.size());
}

void SGFileWriterPlugin::WriteGUID(QUuid x){
    (*(*this).s) << x;
}
