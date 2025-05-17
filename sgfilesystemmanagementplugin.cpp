#include "sgfilesystemmanagementplugin.h"
#include <QDir>
#include "sggenerallibrary.h"

void SGFileSystemManagementPlugin::CreateFolder(QString path){
    QDir d;
    d.mkpath(path);
}

void SGFileSystemManagementPlugin::CreateFile(QString path){
    QDir d;
    d.mkpath(QFileInfo(path).absolutePath());
    QFile f(path);
    f.open(QIODevice::WriteOnly);
    f.close();
}

bool SGFileSystemManagementPlugin::FolderExists(QString path){
    QDir d(path);
    return d.exists();
}

bool SGFileSystemManagementPlugin::FileExists(QString path){
    return QFile::exists(path);
}

void SGFileSystemManagementPlugin::DeleteFile(QString path){
    QFile::remove(path);
}

void SGFileSystemManagementPlugin::MoveFile(QString startpath, QString endpath){
    QFile::rename(startpath, endpath);
}

QString SGFileSystemManagementPlugin::NumberToNCL256(int i){
    QString s = " " + QString::number(i);
    return SGGeneralLibrary::StringToNCL256(s);
}

QString SGFileSystemManagementPlugin::NewFolderPath(QString prefix, QString name){
    QString ncl = SGGeneralLibrary::StringToNCL256(name);
    if(SGFileSystemManagementPlugin::FolderExists(prefix + ncl) == false){return (prefix + ncl);}
    int i = 1;
    while(SGFileSystemManagementPlugin::FolderExists(prefix + ncl + SGFileSystemManagementPlugin::NumberToNCL256(i))){i++;}
    return (prefix + ncl + SGFileSystemManagementPlugin::NumberToNCL256(i));
}

QString SGFileSystemManagementPlugin::NewFilePath(QString prefix, QString name, QString suffix){
    QString ncl = SGGeneralLibrary::StringToNCL256(name);
    if(SGFileSystemManagementPlugin::FileExists(prefix + ncl + suffix) == false){return (prefix + ncl + suffix);}
    int i = 1;
    while(SGFileSystemManagementPlugin::FileExists(prefix + ncl + SGFileSystemManagementPlugin::NumberToNCL256(i) + suffix)){i++;}
    return (prefix + ncl + SGFileSystemManagementPlugin::NumberToNCL256(i) + suffix);
}

QStringList SGFileSystemManagementPlugin::GetFilesInFolder(QString path){
    QDir d(path);
    return d.entryList(QDir::Files | QDir::NoDotAndDotDot);
}

QStringList SGFileSystemManagementPlugin::GetFoldersInFolder(QString path){
    QDir d(path);
    return d.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
}
