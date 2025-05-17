#include "sgfilereaderplugin.h"

SGFileReaderPlugin::SGFileReaderPlugin(QString path){
    (*this).f = new QFile(path);
    (*(*this).f).open(QIODevice::ReadOnly);
    (*this).s = new QDataStream((*this).f);
}

SGFileReaderPlugin::~SGFileReaderPlugin(){
    (*(*this).f).close();
    delete s;
    delete f;
}

bool SGFileReaderPlugin::ReadBool(){
    bool x;
    (*(*this).s) >> x;
    return x;
}

int SGFileReaderPlugin::ReadInt(){
    int x;
    (*(*this).s) >> x;
    return x;
}

uint SGFileReaderPlugin::ReadUint(){
    uint x;
    (*(*this).s) >> x;
    return x;
}

float SGFileReaderPlugin::ReadFloat(){
    float x;
    (*(*this).s) >> x;
    return x;
}

QByteArray SGFileReaderPlugin::ReadString(int l){
    QByteArray x(l, Qt::Uninitialized);
    (*(*this).s).readRawData(x.data(), l);
    return x;
}

QUuid SGFileReaderPlugin::ReadGUID(){
    QUuid x;
    (*(*this).s) >> x;
    return x;
}

bool SGFileReaderPlugin::EndOfStream(){
    return (*(*this).f).atEnd();
}
