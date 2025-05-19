#include "sgnoteslistmanagement.h"
#include "sgcentralmanagement.h"
#include "sggenerallibrary.h"
#include "sgfilesystemmanagementplugin.h"
#include "sgtextbutton022111121.h"
#include "sgtext022111121.h"
#include "sgiconbutton022111121.h"
#include "sgfilereaderplugin.h"
#include "sgfiletypeenum.h"
#include "sgdirectoryviewmanagement.h"
#include "sgstatusbarmanagement.h"

SGText012211121* SGNotesListManagement::folderaddressdisplay = nullptr;
SGScrollView000231100* SGNotesListManagement::noteslistscrollview = nullptr;
SGLayoutNotesList* SGNotesListManagement::noteslistslayout = nullptr;

void SGNotesListManagement::noteslistinitialise(){
    SGNotesListManagement::folderaddressdisplay = new SGText012211121(SGCentralManagement::mainbackground, "", 0.0f, 1.5f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteslist, SGNotesListManagement::folderaddressdisplay, &SGText012211121::ResizeObj);
    SGNotesListManagement::noteslistscrollview = new SGScrollView000231100(SGCentralManagement::mainbackground, 0.0f, 2.5f, 1.0f, -2.5f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteslist, SGNotesListManagement::noteslistscrollview, &SGScrollView000231100::ResizeObj);
    SGNotesListManagement::noteslistslayout = new SGLayoutNotesList(SGNotesListManagement::noteslistscrollview);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteslist, SGNotesListManagement::noteslistslayout, &SGLayoutNotesList::ReceiveUpdateCall);
    (*SGNotesListManagement::noteslistscrollview).setWidget(SGNotesListManagement::noteslistslayout);
    (*SGNotesListManagement::noteslistslayout).ReceiveUpdateCall();
    SGNotesListManagement::refreshnoteslist();
}

void SGNotesListManagement::refreshnoteslist(){
    QString s = " ROOTPATH";
    for(int i=0; i<(*SGCentralManagement::openfilepath).size(); i++){
        s += (" > " + SGGeneralLibrary::NCL256ToString((*SGCentralManagement::openfilepath)[i]));
    }
    (*SGNotesListManagement::folderaddressdisplay).setText(s);

    if((*SGNotesListManagement::noteslistslayout).buttonslist != nullptr){
        for(int i=0; i<(*SGNotesListManagement::noteslistslayout).n; i++){
            delete (*SGNotesListManagement::noteslistslayout).buttonslist[i];
        }
        delete[] (*SGNotesListManagement::noteslistslayout).buttonslist;
    }

    QString mergedpath = SGCentralManagement::mergedfilepath();
    QStringList folders = SGFileSystemManagementPlugin::GetFoldersInFolder(mergedpath);
    QStringList files = SGFileSystemManagementPlugin::GetFilesInFolder(mergedpath);
    (*SGNotesListManagement::noteslistslayout).n = files.size() + folders.size();
    (*SGNotesListManagement::noteslistslayout).buttonslist = new SGNotesListIcon*[(*SGNotesListManagement::noteslistslayout).n];

    for(int i=0; i<folders.size(); i++){
        (*SGNotesListManagement::noteslistslayout).buttonslist[i] = new SGNotesListIcon(SGNotesListManagement::noteslistslayout, 4.0f, 7.0f, folders[i]);
        connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteslist, (*SGNotesListManagement::noteslistslayout).buttonslist[i], &SGNotesListIcon::ResizeObj);
        connect((*SGNotesListManagement::noteslistslayout).buttonslist[i], &SGNotesListIcon::clicked, (*SGNotesListManagement::noteslistslayout).buttonslist[i], &SGNotesListIcon::openfolder);
        QString fname = SGGeneralLibrary::NCL256ToString(folders[i]);
        QString* ws = SGGeneralLibrary::getwrappedtext(fname);

        if(ws[0] == "1"){
            SGTextButton022111121* namedisplay = new SGTextButton022111121((*SGNotesListManagement::noteslistslayout).buttonslist[i], ws[1], 0.0f, 6.0, 4.0f, 0.66f);
            connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteslist, namedisplay, &SGTextButton022111121::ResizeObj);
            connect(namedisplay, &SGTextButton022111121::clicked, (*SGNotesListManagement::noteslistslayout).buttonslist[i], &SGNotesListIcon::openfolder);
        }
        else{
            SGTextButton022111121* namedisplay1 = new SGTextButton022111121((*SGNotesListManagement::noteslistslayout).buttonslist[i], ws[1], 0.0f, 5.66, 4.0f, 0.66f);
            connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteslist, namedisplay1, &SGTextButton022111121::ResizeObj);
            connect(namedisplay1, &SGTextButton022111121::clicked, (*SGNotesListManagement::noteslistslayout).buttonslist[i], &SGNotesListIcon::openfolder);
            SGTextButton022111121* namedisplay2 = new SGTextButton022111121((*SGNotesListManagement::noteslistslayout).buttonslist[i], ws[2], 0.0f, 6.33, 4.0f, 0.66f);
            connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteslist, namedisplay2, &SGTextButton022111121::ResizeObj);
            connect(namedisplay2, &SGTextButton022111121::clicked, (*SGNotesListManagement::noteslistslayout).buttonslist[i], &SGNotesListIcon::openfolder);
        }
        delete[] ws;

        SGIconButton022111121* icon = new SGIconButton022111121((*SGNotesListManagement::noteslistslayout).buttonslist[i], "\uE011", 0.0f, 1.0f, 4.0f, 3.66f);
        connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteslist, icon, &SGIconButton022111121::ResizeObj);
        connect(icon, &SGIconButton022111121::clicked, (*SGNotesListManagement::noteslistslayout).buttonslist[i], &SGNotesListIcon::openfolder);
    }

    for(int i=0; i<files.size(); i++){
        (*SGNotesListManagement::noteslistslayout).buttonslist[folders.size() + i] = new SGNotesListIcon(SGNotesListManagement::noteslistslayout, 4.0f, 7.0f, files[i]);
        connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteslist, (*SGNotesListManagement::noteslistslayout).buttonslist[folders.size() + i], &SGNotesListIcon::ResizeObj);
        QString fname = files[i];
        bool isnote = false;
        if(fname.size() >= 9 && fname.right(9) == QString(".singnote")){
            fname = fname.left(fname.size() - 9);
            fname = SGGeneralLibrary::NCL256ToString(fname);
            isnote = true;
        }
        QString* ws = SGGeneralLibrary::getwrappedtext(fname);

        SGTextButton022111121* namedisplay = nullptr;
        SGTextButton022111121* namedisplay1 = nullptr;
        SGTextButton022111121* namedisplay2 = nullptr;
        SGIconButton022111121* newnoteicon = nullptr;
        if(ws[0] == "1"){
            namedisplay = new SGTextButton022111121((*SGNotesListManagement::noteslistslayout).buttonslist[folders.size() + i], ws[1], 0.0f, 6.0f, 4.0f, 0.66f);
            connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteslist, namedisplay, &SGTextButton022111121::ResizeObj);
        }
        else{
            namedisplay1 = new SGTextButton022111121((*SGNotesListManagement::noteslistslayout).buttonslist[folders.size() + i], ws[1], 0.0f, 5.66f, 4.0f, 0.66f);
            connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteslist, namedisplay1, &SGTextButton022111121::ResizeObj);
            namedisplay2 = new SGTextButton022111121((*SGNotesListManagement::noteslistslayout).buttonslist[folders.size() + i], ws[2], 0.0f, 6.33f, 4.0f, 0.66f);
            connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteslist, namedisplay2, &SGTextButton022111121::ResizeObj);
        }
        delete[] ws;

        if(isnote == true){
            {
                SGFileReaderPlugin r(mergedpath + "/" + files[i]);
                int version = r.ReadInt();
                if(version != 1){isnote = false;}
                else{
                    int filetype = r.ReadInt();
                    if(filetype != SGFileTypeEnum::Note){isnote = false;}
                    else{
                        bool isnew = r.ReadBool();
                        if(isnew){
                            newnoteicon = new SGIconButton022111121((*SGNotesListManagement::noteslistslayout).buttonslist[folders.size() + i], "\uE010", 0.0f, 1.0f, 4.0f, 3.66f);
                            connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteslist, newnoteicon, &SGIconButton022111121::ResizeObj);
                        }
                        else{
                            // add preview image
                        }
                    }
                }
            }
        }

        if(isnote == false){
            SGText022111121* icon = new SGText022111121((*SGNotesListManagement::noteslistslayout).buttonslist[folders.size() + i], "?", 0.0f, 0.0f, 4.0f, 5.66f);
            connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteslist, icon, &SGText022111121::ResizeObj);
        }
        else{
            connect((*SGNotesListManagement::noteslistslayout).buttonslist[folders.size() + i], &SGNotesListIcon::clicked, (*SGNotesListManagement::noteslistslayout).buttonslist[folders.size() + i], &SGNotesListIcon::openfile);
            if(namedisplay != nullptr){connect(namedisplay, &SGTextButton022111121::clicked, (*SGNotesListManagement::noteslistslayout).buttonslist[folders.size() + i], &SGNotesListIcon::openfile);}
            if(namedisplay1 != nullptr){connect(namedisplay1, &SGTextButton022111121::clicked, (*SGNotesListManagement::noteslistslayout).buttonslist[folders.size() + i], &SGNotesListIcon::openfile);}
            if(namedisplay2 != nullptr){connect(namedisplay2, &SGTextButton022111121::clicked, (*SGNotesListManagement::noteslistslayout).buttonslist[folders.size() + i], &SGNotesListIcon::openfile);}
            if(newnoteicon != nullptr){connect(newnoteicon, &SGIconButton022111121::clicked, (*SGNotesListManagement::noteslistslayout).buttonslist[folders.size() + i], &SGNotesListIcon::openfile);}
        }
    }
    emit (*SGCentralManagement::signalsemitter).updatenoteslist();
}

void SGNotesListManagement::exitfolder(){
    if((*SGCentralManagement::openfilepath).size() > 0){
        (*SGCentralManagement::openfilepath).pop_back();
        SGNotesListManagement::refreshnoteslist();
    }
    if((*SGCentralManagement::openfilepath).size() == 0){SGGeneralLibrary::SetUIStyle(SGDirectoryViewManagement::exitfolderbutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour2);}
}
