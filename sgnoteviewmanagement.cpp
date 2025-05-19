#include "sgnoteviewmanagement.h"
#include "sgcentralmanagement.h"
#include "sgnotesavingmanagement.h"
#include "sgnotemanagement.h"
#include "sgnoteslistmanagement.h"
#include "sgdirectoryviewmanagement.h"
#include "sgviewportmanagement.h"
#include "sgtouchinputmanagement.h"
#include "sgnotequickmovemanagement.h"
#include <QTimer>
#include "sgtooloptionsmanagement.h"
#include "sgtooltypeenum.h"
#include "sggenerallibrary.h"
#include "sgrenderingrange.h"
#include "sgfavouritetoolsmanagement.h"
#include "sgpenstrokeselectormanagement.h"

float SGNoteViewManagement::renderw = 0.0f;
float SGNoteViewManagement::renderh = 0.0f;
SGWidget000221103* SGNoteViewManagement::noteviewbackground = nullptr;
SGWidget000331104* SGNoteViewManagement::renderarea = nullptr;
SGWidget000211103* SGNoteViewManagement::toolbarbackground = nullptr;
SGLayoutNoteToolbar* SGNoteViewManagement::toolbarlayout = nullptr;
SGNoteBackgroundRenderer* SGNoteViewManagement::backgroundrenderer = nullptr;
SGIconButton022110032* SGNoteViewManagement::exitnotebutton = nullptr;
SGNoteViewTouchProcessor* SGNoteViewManagement::touchprocessor = nullptr;
SGNoteQuickMoveRenderer* SGNoteViewManagement::quickmoverenderer = nullptr;
bool SGNoteViewManagement::quickmoveenabled = false;
SGFavouriteToolButton* SGNoteViewManagement::changetoolbutton = nullptr;
SGNotePenStrokeRenderer* SGNoteViewManagement::penstrokerenderer = nullptr;
SGNoteUIRenderer* SGNoteViewManagement::uirenderer = nullptr;
SGNoteHighlighterStrokeRenderer* SGNoteViewManagement::highlighterstrokerenderer = nullptr;
SGWidget000133103* SGNoteViewManagement::favouritetoolsbackground = nullptr;
SGScrollView000231100* SGNoteViewManagement::favouritetoolsscrollview = nullptr;
SGLayoutFavouriteTools* SGNoteViewManagement::favouritetoolslayout = nullptr;
SGIconButton022111132* SGNoteViewManagement::favouritetoolsaddbutton = nullptr;
SGIconButton022111132* SGNoteViewManagement::favouritetoolsremovebutton = nullptr;

void SGNoteViewManagement::initialisenoteview(){
    if(SGNoteViewManagement::noteviewbackground != nullptr){
        (*SGNoteViewManagement::noteviewbackground).show();
        emit (*SGCentralManagement::signalsemitter).updatenoteview();
    }
    else{
        SGNoteViewManagement::noteviewbackground = new SGWidget000221103(SGCentralManagement::mainbackground, 0.0f, 0.0f);
        connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteview, SGNoteViewManagement::noteviewbackground, &SGWidget000221103::ResizeObj);
        SGNoteViewManagement::renderarea = new SGWidget000331104(SGNoteViewManagement::noteviewbackground, 0.0f, 1.5f, 1.0f, -3.0f, 1.0f, -1.5f);
        connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteview, SGNoteViewManagement::renderarea, &SGWidget000331104::ResizeObj);

        SGNoteViewManagement::backgroundrenderer = new SGNoteBackgroundRenderer(SGNoteViewManagement::renderarea);
        connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteview, SGNoteViewManagement::backgroundrenderer, &SGNoteBackgroundRenderer::ResizeObj);
        SGNoteViewManagement::penstrokerenderer = new SGNotePenStrokeRenderer(SGNoteViewManagement::renderarea);
        connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteview, SGNoteViewManagement::penstrokerenderer, &SGNotePenStrokeRenderer::ResizeObj);
        SGNoteViewManagement::highlighterstrokerenderer = new SGNoteHighlighterStrokeRenderer(SGNoteViewManagement::renderarea);
        connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteview, SGNoteViewManagement::highlighterstrokerenderer, &SGNoteHighlighterStrokeRenderer::ResizeObj);
        SGNoteViewManagement::uirenderer = new SGNoteUIRenderer(SGNoteViewManagement::renderarea);
        connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteview, SGNoteViewManagement::uirenderer, &SGNoteUIRenderer::ResizeObj);
        SGNoteViewManagement::quickmoverenderer = new SGNoteQuickMoveRenderer(SGNoteViewManagement::renderarea);
        connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteview, SGNoteViewManagement::quickmoverenderer, &SGNoteQuickMoveRenderer::ResizeObj);
        SGNoteViewManagement::touchprocessor = new SGNoteViewTouchProcessor(SGNoteViewManagement::renderarea);
        connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteview, SGNoteViewManagement::touchprocessor, &SGNoteViewTouchProcessor::ResizeObj);

        SGNoteViewManagement::toolbarbackground = new SGWidget000211103(SGNoteViewManagement::noteviewbackground, 0.0f, 0.0f, 1.5f);
        connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteview, SGNoteViewManagement::toolbarbackground, &SGWidget000211103::ResizeObj);
        SGNoteViewManagement::toolbarlayout = new SGLayoutNoteToolbar(SGNoteViewManagement::toolbarbackground);
        connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteview, SGNoteViewManagement::toolbarlayout, &SGLayoutNoteToolbar::ReceiveUpdateCall);
        SGNoteViewManagement::exitnotebutton = new SGIconButton022110032(SGNoteViewManagement::toolbarlayout, "\uE014", 1.5f, 1.5f);
        connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteview, SGNoteViewManagement::exitnotebutton, &SGIconButton022110032::ResizeObj);
        connect(SGNoteViewManagement::exitnotebutton, &SGIconButton022110032::clicked, &SGNoteViewManagement::exitnote);
        (*SGNoteViewManagement::toolbarlayout).objlist[0] = SGNoteViewManagement::exitnotebutton;
        SGNoteViewManagement::changetoolbutton = new SGFavouriteToolButton(SGNoteViewManagement::toolbarlayout, SGToolTypeEnum::Move, 0xFF00C8FF, 2.0f);
        connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteview, SGNoteViewManagement::changetoolbutton, &SGFavouriteToolButton::ResizeObj);
        disconnect((*SGNoteViewManagement::changetoolbutton).connection);
        connect((*SGNoteViewManagement::changetoolbutton).buttonicon, &SGIconButton022111132::clicked, &SGToolOptionsManagement::showtooloptions);
        (*SGNoteViewManagement::toolbarlayout).objlist[1] = SGNoteViewManagement::changetoolbutton;

        SGNoteViewManagement::favouritetoolsbackground = new SGWidget000133103(SGNoteViewManagement::noteviewbackground, 3.0f, 1.5f, 3.0f, 1.0f, -1.5f);
        connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteview, SGNoteViewManagement::favouritetoolsbackground, &SGWidget000133103::ResizeObj);
        SGNoteViewManagement::favouritetoolsscrollview = new SGScrollView000231100(SGNoteViewManagement::favouritetoolsbackground, 0.0f, 1.5f, 1.0f, -1.5f);
        connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteview, SGNoteViewManagement::favouritetoolsscrollview, &SGScrollView000231100::ResizeObj);
        SGNoteViewManagement::favouritetoolslayout = new SGLayoutFavouriteTools(SGNoteViewManagement::favouritetoolsscrollview);
        connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteview, SGNoteViewManagement::favouritetoolslayout, &SGLayoutFavouriteTools::ReceiveUpdateCall);
        (*SGNoteViewManagement::favouritetoolsscrollview).setWidget(SGNoteViewManagement::favouritetoolslayout);
        (*SGNoteViewManagement::favouritetoolslayout).ReceiveUpdateCall();
        SGNoteViewManagement::favouritetoolsaddbutton = new SGIconButton022111132(SGNoteViewManagement::favouritetoolsbackground, "\uE022", 0.0f, 0.0f, 1.5f, 1.5f);
        connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteview, SGNoteViewManagement::favouritetoolsaddbutton, &SGIconButton022111132::ResizeObj);
        connect(SGNoteViewManagement::favouritetoolsaddbutton, &SGIconButton022111132::clicked, &SGFavouriteToolsManagement::addfavouritetool);
        SGNoteViewManagement::favouritetoolsremovebutton = new SGIconButton022111132(SGNoteViewManagement::favouritetoolsbackground, "\uE023", 1.5f, 0.0f, 1.5f, 1.5f);
        connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatenoteview, SGNoteViewManagement::favouritetoolsremovebutton, &SGIconButton022111132::ResizeObj);
        connect(SGNoteViewManagement::favouritetoolsremovebutton, &SGIconButton022111132::clicked, &SGFavouriteToolsManagement::togglefavouritetool);
        SGGeneralLibrary::SetUIStyle(SGNoteViewManagement::favouritetoolsremovebutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
        SGFavouriteToolsManagement::loadfavouritetools();
    }

    SGTouchInputManagement::quickmovetimer = new QElapsedTimer();
    (*SGTouchInputManagement::quickmovetimer).start();
    SGNoteQuickMoveManagement::quickmovetimer = new QTimer();
    connect(SGNoteQuickMoveManagement::quickmovetimer, &QTimer::timeout, &SGNoteQuickMoveManagement::applyquickmove);
}

void SGNoteViewManagement::exitnote(){
    SGNoteViewManagement::deleteselectors();
    SGNoteSavingManagement::savenote(SGCentralManagement::mergedfilepath());
    SGNoteManagement::noteisopen = false;
    SGNoteManagement::penstrokezindex = 0;
    SGNoteManagement::highlighterstrokezindex = 0;
    for(int i=0; i<(*SGNoteManagement::notedata).size(); i++){delete (*SGNoteManagement::notedata)[i];}
    delete SGNoteManagement::notedata;
    for(QHash<int, SGRenderingRange*>::iterator i = (*SGNoteManagement::renderingdata).begin(); i != (*SGNoteManagement::renderingdata).end(); i++){delete i.value();}
    delete SGNoteManagement::renderingdata;
    for(QHash<int, SGColliderRange*>::iterator i = (*SGNoteManagement::collidersdata).begin(); i != (*SGNoteManagement::collidersdata).end(); i++){delete i.value();}
    delete SGNoteManagement::collidersdata;
    SGCentralManagement::activetooltype = SGToolTypeEnum::Move;
    SGCentralManagement::focusedpositionx = 0.0f;
    SGCentralManagement::focusedpositiony = 0.0f;
    SGCentralManagement::focusedzoom = 0.0f;
    SGCentralManagement::pagew = 0.0f;
    SGCentralManagement::pageh = 0.0f;
    SGCentralManagement::marginx = 0.0f;
    SGCentralManagement::marginy = 0.0f;
    SGFavouriteToolsManagement::isdeleting = false;
    SGGeneralLibrary::SetUIStyle(SGNoteViewManagement::favouritetoolsaddbutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
    SGGeneralLibrary::SetUIStyle(SGNoteViewManagement::favouritetoolsremovebutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    (*SGCentralManagement::openfilepath).pop_back();
    (*SGNoteViewManagement::noteviewbackground).hide();
    (*SGNotesListManagement::folderaddressdisplay).show();
    (*SGNotesListManagement::noteslistscrollview).show();
    (*SGDirectoryViewManagement::toolbarbackground).show();
    emit (*SGCentralManagement::signalsemitter).updatenoteslist();
    emit (*SGCentralManagement::signalsemitter).updatedirectorytoolbar();
}

void SGNoteViewManagement::updaterendering(){
    (*SGNoteViewManagement::backgroundrenderer).update();
    (*SGNoteViewManagement::penstrokerenderer).update();
    (*SGNoteViewManagement::highlighterstrokerenderer).update();
    (*SGNoteViewManagement::uirenderer).update();
}

void SGNoteViewManagement::deleteselectors(){
    SGPenStrokeSelectorManagement::deleteselector();
}
