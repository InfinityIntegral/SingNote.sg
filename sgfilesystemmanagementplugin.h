#ifndef SGFILESYSTEMMANAGEMENTPLUGIN_H
#define SGFILESYSTEMMANAGEMENTPLUGIN_H

#include <QObject>

class SGFileSystemManagementPlugin : public QObject
{
    Q_OBJECT
public:
    static void CreateFolder(QString path);
    static void CreateFile(QString path);
    static bool FolderExists(QString path);
    static bool FileExists(QString path);
    static void DeleteFile(QString path);
    static void MoveFile(QString startpath, QString endpath);
    static QString NewFolderPath(QString prefix, QString name);
    static QString NewFilePath(QString prefix, QString name, QString suffix);
    static QString NumberToNCL256(int i);
    static QStringList GetFilesInFolder(QString path);
    static QStringList GetFoldersInFolder(QString path);

private:
    SGFileSystemManagementPlugin(){}
    ~SGFileSystemManagementPlugin(){}
};

#endif // SGFILESYSTEMMANAGEMENTPLUGIN_H
