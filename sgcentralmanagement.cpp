#include "sgcentralmanagement.h"
#include "sgstatusbarmanagement.h"
#include <QFontDatabase>
#include "sggenerallibrary.h"
#include "sgdirectoryviewmanagement.h"
#include <QStandardPaths>
#include "sgnoteslistmanagement.h"
#include <QCoreApplication>
#include "sgnoteviewmanagement.h"
#include "sgtouchinputmanagement.h"
#include "sgnotequickmovemanagement.h"
#include "sgtooltypeenum.h"
#include "sgnoteinteractionmodeenum.h"
#include "sgnotemanagement.h"

QString SGCentralManagement::colour0 = "rgba(255, 255, 255, 0)";
QString SGCentralManagement::colour1 = "rgba(255, 0, 200, 255)";
QString SGCentralManagement::colour2 = "rgba(255, 255, 255, 255)";
QString SGCentralManagement::colour3 = "rgba(255, 128, 228, 255)";
float SGCentralManagement::screenw = 0.0f;
float SGCentralManagement::screenh = 0.0f;
float SGCentralManagement::renderw = 0.0f;
float SGCentralManagement::renderh = 0.0f;
float SGCentralManagement::sizeunit = 0.0f;
SGRootWindow* SGCentralManagement::rootwindow = nullptr;
SGSignalsEmitter* SGCentralManagement::signalsemitter = nullptr;
SGWidget000451103* SGCentralManagement::mainbackground = nullptr;
QFont* SGCentralManagement::SingNoteIcons = nullptr;
QVector<QString>* SGCentralManagement::openfilepath = nullptr;
QString SGCentralManagement::rootfilepath = "";
float SGCentralManagement::focusedpositionx = 0.0f;
float SGCentralManagement::focusedpositiony = 0.0f;
float SGCentralManagement::focusedzoom = 0.0f;
float SGCentralManagement::pagew = 0.0f;
float SGCentralManagement::pageh = 0.0f;
float SGCentralManagement::marginx = 0.0f;
float SGCentralManagement::marginy = 0.0f;
int SGCentralManagement::interactionmode = SGNoteInteractionModeEnum::DrawOnly;
int SGCentralManagement::activetooltype = SGToolTypeEnum::Move;
uint SGCentralManagement::activetoolcolour = 0xFF00C8FF;
float SGCentralManagement::activetoolwidth = 2.0f;
float SGCentralManagement::writeprecision = 0.1f;

QString SGCentralManagement::mergedfilepath(){
    QString s = SGCentralManagement::rootfilepath + "NOTES";
    for(int i=0; i<(*SGCentralManagement::openfilepath).size(); i++){
        s += ("/" + (*SGCentralManagement::openfilepath)[i]);
    }
    return s;
}

void SGCentralManagement::initialise(){
    connect(qApp, &QCoreApplication::aboutToQuit, &SGCentralManagement::terminate);
    QCoreApplication::setAttribute(Qt::AA_SynthesizeTouchForUnhandledMouseEvents);
    QCoreApplication::setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents);

    QList templist = QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/assets/SingScript.sg.otf"));
    SGGeneralLibrary::SingScriptSG = new QFont(templist.first());
    templist = QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/assets/SingNote.sg-icons.otf"));
    SGCentralManagement::SingNoteIcons = new QFont(templist.first());

    SGCentralManagement::signalsemitter = new SGSignalsEmitter();
    SGCentralManagement::rootwindow = new SGRootWindow();
    SGCentralManagement::rootfilepath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/SingNote.sg/";
    SGCentralManagement::openfilepath = new QVector<QString>();
    (*SGCentralManagement::rootwindow).updatescreensize();
    SGStatusBarManagement::initialisestatusbar();
    SGCentralManagement::mainbackground = new SGWidget000451103(SGCentralManagement::rootwindow, 0.0f, 1.0f, 1.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatescreen, SGCentralManagement::mainbackground, &SGWidget000451103::ResizeObj);
    SGNoteViewManagement::initialisenoteview();
    (*SGNoteViewManagement::noteviewbackground).hide();
    SGDirectoryViewManagement::initialisedirectorytoolbar();
    SGNotesListManagement::noteslistinitialise();
}

void SGCentralManagement::terminate(){
    if(SGNoteManagement::noteisopen){SGNoteViewManagement::exitnote();}
    delete SGCentralManagement::rootwindow;
    delete SGCentralManagement::openfilepath;
    delete SGCentralManagement::SingNoteIcons;
    delete SGGeneralLibrary::SingScriptSG;
    delete SGTouchInputManagement::quickmovetimer;
    delete SGNoteQuickMoveManagement::quickmovetimer;
}
