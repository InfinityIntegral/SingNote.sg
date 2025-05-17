#include "sgdirectoryviewmanagement.h"
#include "sgcentralmanagement.h"
#include "sgnewfilesmanagement.h"
#include "sgnoteslistmanagement.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"

SGWidget000211103* SGDirectoryViewManagement::toolbarbackground = nullptr;
SGLayoutDirectoryToolbar* SGDirectoryViewManagement::toolbarlayout = nullptr;
SGIconButton022110032* SGDirectoryViewManagement::newfilebutton = nullptr;
SGIconButton022110032* SGDirectoryViewManagement::exitfolderbutton = nullptr;
SGIconButton022110032* SGDirectoryViewManagement::refreshnoteslistsbutton = nullptr;

void SGDirectoryViewManagement::initialisedirectorytoolbar(){
    SGDirectoryViewManagement::toolbarbackground = new SGWidget000211103(SGCentralManagement::mainbackground, 0.0f, 0.0f, 1.5f);
    // leave it like this for now, later when the other icons are here then let the height fit to icons, with the app logo on the left, have a SGDirectoryViewManagement::ResponsiveUI to change resizing parameters according to aspect ratio
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatedirectorytoolbar, SGDirectoryViewManagement::toolbarbackground, &SGWidget000211103::ResizeObj);
    SGDirectoryViewManagement::toolbarlayout = new SGLayoutDirectoryToolbar(SGDirectoryViewManagement::toolbarbackground);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatedirectorytoolbar, SGDirectoryViewManagement::toolbarlayout, &SGLayoutDirectoryToolbar::ReceiveUpdateCall);

    SGDirectoryViewManagement::newfilebutton = new SGIconButton022110032(SGDirectoryViewManagement::toolbarlayout, QString("\uE010"), 1.5f, 1.5f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatedirectorytoolbar, SGDirectoryViewManagement::newfilebutton, &SGIconButton022110032::ResizeObj);
    connect(SGDirectoryViewManagement::newfilebutton, &SGIconButton022110032::clicked, &SGNewFilesManagement::shownewfilemenu);
    (*SGDirectoryViewManagement::toolbarlayout).objlist[0] = SGDirectoryViewManagement::newfilebutton;

    SGDirectoryViewManagement::exitfolderbutton = new SGIconButton022110032(SGDirectoryViewManagement::toolbarlayout, "\uE012", 1.5f, 1.5f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatedirectorytoolbar, SGDirectoryViewManagement::exitfolderbutton, &SGIconButton022110032::ResizeObj);
    connect(SGDirectoryViewManagement::exitfolderbutton, &SGIconButton022110032::clicked, &SGNotesListManagement::exitfolder);
    (*SGDirectoryViewManagement::toolbarlayout).objlist[1] = SGDirectoryViewManagement::exitfolderbutton;
    SGGeneralLibrary::SetUIStyle(SGDirectoryViewManagement::exitfolderbutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour2);

    SGDirectoryViewManagement::refreshnoteslistsbutton = new SGIconButton022110032(SGDirectoryViewManagement::toolbarlayout, "\uE013", 1.5f, 1.5f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatedirectorytoolbar, SGDirectoryViewManagement::refreshnoteslistsbutton, &SGIconButton022110032::ResizeObj);
    connect(SGDirectoryViewManagement::refreshnoteslistsbutton, &SGIconButton022110032::clicked, &SGNotesListManagement::refreshnoteslist);
    (*SGDirectoryViewManagement::toolbarlayout).objlist[2] = SGDirectoryViewManagement::refreshnoteslistsbutton;
}
