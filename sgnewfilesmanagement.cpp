#include "sgnewfilesmanagement.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"
#include "sgfilesystemmanagementplugin.h"
#include "sgfilewriterplugin.h"
#include "sgfiletypeenum.h"
#include "sgnoteobjecttypeenum.h"
#include <QUuid>
#include "sgnoteslistmanagement.h"

SGWidget000221104* SGNewFilesManagement::newfilemenubackground = nullptr;
SGTextButton022211332* SGNewFilesManagement::newfilemenucancel = nullptr;
SGTextButton022211232* SGNewFilesManagement::newfilemenunewfile = nullptr;
SGTextButton022211232* SGNewFilesManagement::newfilemenunewfolder = nullptr;
int SGNewFilesManagement::newitemtype = 0;
SGWidget000221104* SGNewFilesManagement::newfilewindowbackground = nullptr;
SGText012211223* SGNewFilesManagement::newfilewindowprompt = nullptr;
SGInputField312211232* SGNewFilesManagement::newfilewindownameinput = nullptr;
SGTextButton022314332* SGNewFilesManagement::newfilewindowcancel = nullptr;
SGTextButton022314332* SGNewFilesManagement::newfilewindowconfirm = nullptr;

void SGNewFilesManagement::shownewfilemenu(){
    if(SGNewFilesManagement::newfilemenubackground != nullptr){
        (*SGNewFilesManagement::newfilemenubackground).show();
        emit (*SGCentralManagement::signalsemitter).updatenewfilemenu();
        return;
    }
    SGNewFilesManagement::newfilemenubackground = new SGWidget000221104(SGCentralManagement::mainbackground, 0.0f, 0.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenewfilemenu, SGNewFilesManagement::newfilemenubackground, &SGWidget000221104::ResizeObj);
    SGNewFilesManagement::newfilemenucancel = new SGTextButton022211332(SGNewFilesManagement::newfilemenubackground, "cancel", 0.0f, 1.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenewfilemenu, SGNewFilesManagement::newfilemenucancel, &SGTextButton022211332::ResizeObj);
    connect(SGNewFilesManagement::newfilemenucancel, &SGTextButton022211332::clicked, &SGNewFilesManagement::hidenewfilemenu);
    SGNewFilesManagement::newfilemenunewfile = new SGTextButton022211232(SGNewFilesManagement::newfilemenubackground, "create new note", 0.0f, -1.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenewfilemenu, SGNewFilesManagement::newfilemenunewfile, &SGTextButton022211232::ResizeObj);
    connect(SGNewFilesManagement::newfilemenunewfile, &SGTextButton022211232::clicked, &SGNewFilesManagement::newfilewindownewfile);
    SGNewFilesManagement::newfilemenunewfolder = new SGTextButton022211232(SGNewFilesManagement::newfilemenubackground, "create new folder", 0.0f, 0.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenewfilemenu, SGNewFilesManagement::newfilemenunewfolder, &SGTextButton022211232::ResizeObj);
    connect(SGNewFilesManagement::newfilemenunewfolder, &SGTextButton022211232::clicked, &SGNewFilesManagement::newfilewindownewfolder);
}

void SGNewFilesManagement::hidenewfilemenu(){
    (*SGNewFilesManagement::newfilemenubackground).hide();
}

void SGNewFilesManagement::newfilewindownewfile(){
    SGNewFilesManagement::newitemtype = 0;
    SGNewFilesManagement::shownewfilewindow();
}

void SGNewFilesManagement::newfilewindownewfolder(){
    SGNewFilesManagement::newitemtype = 1;
    SGNewFilesManagement::shownewfilewindow();
}

void SGNewFilesManagement::shownewfilewindow(){
    if(SGNewFilesManagement::newfilewindowbackground != nullptr){
        (*SGNewFilesManagement::newfilewindowbackground).show();
        if(SGNewFilesManagement::newitemtype == 0){(*SGNewFilesManagement::newfilewindowprompt).setText("Enter the name of your new note:");}
        else if(SGNewFilesManagement::newitemtype == 1){(*SGNewFilesManagement::newfilewindowprompt).setText("Enter the name of your new folder:");}
        emit (*SGCentralManagement::signalsemitter).updatenewfilewindow();
        return;
    }
    SGNewFilesManagement::newfilewindowbackground = new SGWidget000221104(SGCentralManagement::mainbackground, 0.0f, 0.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenewfilewindow, SGNewFilesManagement::newfilewindowbackground, &SGWidget000221104::ResizeObj);
    SGNewFilesManagement::newfilewindowprompt = new SGText012211223(SGNewFilesManagement::newfilewindowbackground, "", 0.0f, -1.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenewfilewindow, SGNewFilesManagement::newfilewindowprompt, &SGText012211223::ResizeObj);
    if(SGNewFilesManagement::newitemtype == 0){(*SGNewFilesManagement::newfilewindowprompt).setText("Enter the name of your new note:");}
    else if(SGNewFilesManagement::newitemtype == 1){(*SGNewFilesManagement::newfilewindowprompt).setText("Enter the name of your new folder:");}
    SGNewFilesManagement::newfilewindownameinput = new SGInputField312211232(SGNewFilesManagement::newfilewindowbackground, 0.0f, 0.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenewfilewindow, SGNewFilesManagement::newfilewindownameinput, &SGInputField312211232::ResizeObj);
    SGNewFilesManagement::newfilewindowcancel = new SGTextButton022314332(SGNewFilesManagement::newfilewindowbackground, "cancel", 0.0f, 0.0f, 1.0f, 0.5f, 0.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenewfilewindow, SGNewFilesManagement::newfilewindowcancel, &SGTextButton022314332::ResizeObj);
    connect(SGNewFilesManagement::newfilewindowcancel, &SGTextButton022314332::clicked, &SGNewFilesManagement::cancelnewfilecreation);
    SGNewFilesManagement::newfilewindowconfirm = new SGTextButton022314332(SGNewFilesManagement::newfilewindowbackground, "confirm", 0.5f, 0.0f, 1.0f, 0.5f, 0.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenewfilewindow, SGNewFilesManagement::newfilewindowconfirm, &SGTextButton022314332::ResizeObj);
    connect(SGNewFilesManagement::newfilewindowconfirm, &SGTextButton022314332::clicked, &SGNewFilesManagement::confirmnewfilecreation);
}

void SGNewFilesManagement::cancelnewfilecreation(){
    (*SGNewFilesManagement::newfilewindowbackground).hide();
    (*SGNewFilesManagement::newfilemenubackground).hide();
    (*SGNewFilesManagement::newfilewindownameinput).setText("");
}

void SGNewFilesManagement::confirmnewfilecreation(){
    (*SGNewFilesManagement::newfilewindowbackground).hide();
    (*SGNewFilesManagement::newfilemenubackground).hide();
    if((*SGNewFilesManagement::newfilewindownameinput).text() == ""){return;}
    if(SGNewFilesManagement::newitemtype == 0){createnewnote();}
    else if(SGNewFilesManagement::newitemtype == 1){createnewfolder();}
    (*SGNewFilesManagement::newfilewindownameinput).setText("");
    SGNotesListManagement::refreshnoteslist();
}

void SGNewFilesManagement::createnewnote(){
    QString path = SGFileSystemManagementPlugin::NewFilePath(SGCentralManagement::mergedfilepath() + "/", (*SGNewFilesManagement::newfilewindownameinput).text(), ".singnote");
    SGFileSystemManagementPlugin::CreateFile(path);
    {
        SGFileWriterPlugin w(path);
        w.WriteInt(1);
        w.WriteInt(SGFileTypeEnum::Note);
        w.WriteBool(true);
        w.WriteInt(0);
        w.WriteInt(0);
        w.WriteInt(0);
        QByteArray ba;
        w.WriteString(ba);
        w.WriteInt(0);
        w.WriteString(ba);
        w.WriteInt(0);
        w.WriteFloat(21.0f);
        w.WriteFloat(29.7f);
        w.WriteFloat(0.5f);
        w.WriteFloat(0.5f);
        w.WriteBool(true);
        w.WriteGUID(SGGeneralLibrary::GetNewGUID());
        w.WriteInt(SGNoteObjectTypeEnum::Background);
        w.WriteInt(1);
        w.WriteInt(0);
        w.WriteString(ba);
    }
}

void SGNewFilesManagement::createnewfolder(){
    SGFileSystemManagementPlugin::CreateFolder(SGFileSystemManagementPlugin::NewFolderPath(SGCentralManagement::mergedfilepath() + "/", (*SGNewFilesManagement::newfilewindownameinput).text()));
}
