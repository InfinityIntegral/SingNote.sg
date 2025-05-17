#ifndef SGNEWFILESMANAGEMENT_H
#define SGNEWFILESMANAGEMENT_H

#include <QObject>
#include "sgwidget000221104.h"
#include "sgtextbutton022211332.h"
#include "sgtextbutton022211232.h"
#include "sgtext012211223.h"
#include "sginputfield312211232.h"
#include "sgtextbutton022314332.h"

class SGNewFilesManagement : public QObject
{
    Q_OBJECT
public:
    static void shownewfilemenu();
    static SGWidget000221104* newfilemenubackground;
    static SGTextButton022211332* newfilemenucancel;
    static void hidenewfilemenu();
    static SGTextButton022211232* newfilemenunewfile;
    static SGTextButton022211232* newfilemenunewfolder;
    static int newitemtype;
    static void newfilewindownewfile();
    static void newfilewindownewfolder();
    static void shownewfilewindow();
    static SGWidget000221104* newfilewindowbackground;
    static SGText012211223* newfilewindowprompt;
    static SGInputField312211232* newfilewindownameinput;
    static SGTextButton022314332* newfilewindowcancel;
    static SGTextButton022314332* newfilewindowconfirm;
    static void cancelnewfilecreation();
    static void confirmnewfilecreation();
    static void createnewnote();
    static void createnewfolder();

private:
    SGNewFilesManagement(){}
    ~SGNewFilesManagement(){}
};

#endif // SGNEWFILESMANAGEMENT_H
