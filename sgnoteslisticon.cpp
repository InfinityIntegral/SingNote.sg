#include "sgnoteslisticon.h"
#include "sgcentralmanagement.h"
#include "sgnoteslistmanagement.h"
#include "sgdirectoryviewmanagement.h"
#include "sggenerallibrary.h"
#include "sgnoteviewmanagement.h"
#include "sgnotesavingmanagement.h"

SGNotesListIcon::SGNotesListIcon(QWidget *parent, float w, float h, QString& s) : SGWidgetButton000110001(parent, w, h){
    (*this).path = s;
}

void SGNotesListIcon::openfolder(){
    (*SGCentralManagement::openfilepath).push_back(path);
    SGNotesListManagement::refreshnoteslist();
    SGGeneralLibrary::SetUIStyle(SGDirectoryViewManagement::exitfolderbutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
}

void SGNotesListIcon::openfile(){
    (*SGCentralManagement::openfilepath).push_back(path);
    (*SGNotesListManagement::noteslistscrollview).hide();
    (*SGNotesListManagement::folderaddressdisplay).hide();
    (*SGDirectoryViewManagement::toolbarbackground).hide();
    SGNoteViewManagement::initialisenoteview();
    SGNoteSavingManagement::opennote(SGCentralManagement::mergedfilepath());
}
