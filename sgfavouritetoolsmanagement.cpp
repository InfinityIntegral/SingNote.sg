#include "sgfavouritetoolsmanagement.h"
#include "sgfavouritetoolbutton.h"
#include "sgnoteviewmanagement.h"
#include "sgcentralmanagement.h"
#include "sgtextbutton022110032.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"
#include <QDebug>
#include "sgfilesystemmanagementplugin.h"
#include "sgfilewriterplugin.h"
#include "sgfilereaderplugin.h"

bool SGFavouriteToolsManagement::isdeleting = false;

void SGFavouriteToolsManagement::addfavouritetool(){
    if(SGFavouriteToolsManagement::isdeleting == false){
        SGFavouriteToolsManagement::createfavouritetoolbutton(SGCentralManagement::activetooltype, SGCentralManagement::activetoolcolour, SGCentralManagement::activetoolwidth);
        SGFavouriteToolsManagement::savefavouritetools();
    }
    else{SGFavouriteToolsManagement::togglefavouritetool();}
}

void SGFavouriteToolsManagement::createfavouritetoolbutton(int type, uint col, float width){
    SGFavouriteToolButton* o = new SGFavouriteToolButton(SGNoteViewManagement::favouritetoolslayout, type, col, width);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteview, o, &SGFavouriteToolButton::ResizeObj);
    (*o).index = (*(*SGNoteViewManagement::favouritetoolslayout).objlist).size();
    (*(*SGNoteViewManagement::favouritetoolslayout).objlist).push_back(o);
    (*SGNoteViewManagement::favouritetoolslayout).ReceiveUpdateCall();
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteview, o, &SGFavouriteToolButton::ResizeObj);
}

void SGFavouriteToolsManagement::togglefavouritetool(){
    if(SGFavouriteToolsManagement::isdeleting == true){
        SGFavouriteToolsManagement::isdeleting = false;
        SGGeneralLibrary::SetUIStyle(SGNoteViewManagement::favouritetoolsaddbutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
        SGGeneralLibrary::SetUIStyle(SGNoteViewManagement::favouritetoolsremovebutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    }
    else{
        SGFavouriteToolsManagement::isdeleting = true;
        SGGeneralLibrary::SetUIStyle(SGNoteViewManagement::favouritetoolsaddbutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
        SGGeneralLibrary::SetUIStyle(SGNoteViewManagement::favouritetoolsremovebutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
    }
}

void SGFavouriteToolsManagement::savefavouritetools(){
    QString filename = "FAVOURITE_TOOLS";
    QString path = SGCentralManagement::rootfilepath + "INTERNAL/" + SGGeneralLibrary::StringToNCL256(filename) + ".sg";
    if(SGFileSystemManagementPlugin::FileExists(path)){SGFileSystemManagementPlugin::DeleteFile(path);}
    SGFileSystemManagementPlugin::CreateFile(path);
    {
        SGFileWriterPlugin w = SGFileWriterPlugin(path);
        for(int i=0; i<(*(*SGNoteViewManagement::favouritetoolslayout).objlist).size(); i++){
            w.WriteInt((*(SGFavouriteToolButton*)((*(*SGNoteViewManagement::favouritetoolslayout).objlist)[i])).tooltype);
            w.WriteUint((*(SGFavouriteToolButton*)((*(*SGNoteViewManagement::favouritetoolslayout).objlist)[i])).toolcolour);
            w.WriteFloat((*(SGFavouriteToolButton*)((*(*SGNoteViewManagement::favouritetoolslayout).objlist)[i])).toolwidth);
        }
    }
}

void SGFavouriteToolsManagement::loadfavouritetools(){
    QString filename = "FAVOURITE_TOOLS";
    QString path = SGCentralManagement::rootfilepath + "INTERNAL/" + SGGeneralLibrary::StringToNCL256(filename) + ".sg";
    if(SGFileSystemManagementPlugin::FileExists(path)){
        SGFileReaderPlugin r = SGFileReaderPlugin(path);
        while(r.EndOfStream() == false){
            int type = r.ReadInt();
            uint col = r.ReadUint();
            float width = r.ReadFloat();
            SGFavouriteToolsManagement::createfavouritetoolbutton(type, col, width);
        }
    }
}
