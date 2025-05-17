#include "sgsignalsemitter.h"
#include "sgdirectoryviewmanagement.h"
#include "sgnewfilesmanagement.h"
#include "sgnoteslistmanagement.h"
#include "sgnoteviewmanagement.h"
#include "sgtooloptionsmanagement.h"

SGSignalsEmitter::SGSignalsEmitter(){

}

void SGSignalsEmitter::sendsignals(){
    emit (*this).updatescreen();
    if(SGDirectoryViewManagement::toolbarbackground != nullptr && (*SGDirectoryViewManagement::toolbarbackground).isVisible()){emit (*this).updatedirectorytoolbar();}
    if(SGNewFilesManagement::newfilemenubackground != nullptr && (*SGNewFilesManagement::newfilemenubackground).isVisible()){emit (*this).updatenewfilemenu();}
    if(SGNewFilesManagement::newfilewindowbackground != nullptr && (*SGNewFilesManagement::newfilewindowbackground).isVisible()){emit (*this).updatenewfilewindow();}
    if(SGNotesListManagement::folderaddressdisplay != nullptr && (*SGNotesListManagement::folderaddressdisplay).isVisible()){emit (*this).updatenoteslist();}
    if(SGNoteViewManagement::noteviewbackground != nullptr && (*SGNoteViewManagement::noteviewbackground).isVisible()){emit updatenoteview();}
    if(SGToolOptionsManagement::changetoolbackground != nullptr && (*SGToolOptionsManagement::changetoolbackground).isVisible()){emit updatechangetoolsmenu();}
    if(SGToolOptionsManagement::changepenbackground != nullptr && (*SGToolOptionsManagement::changepenbackground).isVisible()){emit updatechangepenmenu();}
    if(SGToolOptionsManagement::changeeraserbackground != nullptr && (*SGToolOptionsManagement::changeeraserbackground).isVisible()){emit updatechangeerasermenu();}
    if(SGToolOptionsManagement::changehighlighterbackground != nullptr && (*SGToolOptionsManagement::changehighlighterbackground).isVisible()){emit updatechangehighlightermenu();}
    if(SGToolOptionsManagement::changeselectorbackground != nullptr && (*SGToolOptionsManagement::changeselectorbackground).isVisible()){emit updatechangeselectormenu();}
}
