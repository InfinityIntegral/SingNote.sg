#include "sgfavouritetoolbutton.h"
#include "sgtooltypeenum.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"
#include "sgfavouritetoolsmanagement.h"
#include "sgnoteviewmanagement.h"
#include "sgtooloptionsmanagement.h"

SGFavouriteToolButton::SGFavouriteToolButton(QWidget *parent, int type, uint col, float width) : SGWidget000110001(parent, 1.5f, 1.5f){
    (*this).tooltype = type;
    (*this).toolcolour = col;
    (*this).toolwidth = width;
    (*this).buttonbackground = new SGWidget000111102(this, 0.0f, 0.0f, 1.5f, 1.5f);
    (*this).buttonicon = new SGIconButton022111132(this, "", 0.0f, 0.0f, 1.5f, 1.5f);
    (*this).buttontext = new SGText012211121(this, "", 0.0f, 0.0f, 0.67f);
    SGGeneralLibrary::SetUIStyle(buttontext, SGGeneralLibrary::stylesheetfieldtextcolour, SGCentralManagement::colour2);
    SGGeneralLibrary::SetUIStyle(buttontext, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour0);
    (*buttontext).setAttribute(Qt::WA_TransparentForMouseEvents);
    (*this).refreshicon();
    (*this).connection = connect((*this).buttonicon, &SGIconButton022111132::clicked, this, &SGFavouriteToolButton::setfavourite);
}

void SGFavouriteToolButton::refreshicon(){
    if(tooltype == SGToolTypeEnum::Move){
        (*buttonicon).setText("\uE015");
        SGGeneralLibrary::SetUIStyle(buttonicon, SGGeneralLibrary::stylesheetfieldtextcolour, SGCentralManagement::colour2);
        SGGeneralLibrary::SetUIStyle(buttonicon, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
        (*buttontext).hide();
    }
    else if(tooltype == SGToolTypeEnum::Pen){
        (*buttonicon).setText("\uE01C");
        QString col = SGGeneralLibrary::ColourUintToCSS(toolcolour);
        SGGeneralLibrary::SetUIStyle(buttonicon, SGGeneralLibrary::stylesheetfieldtextcolour, col);
        SGGeneralLibrary::SetUIStyle(buttonicon, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
        (*buttontext).show();
        (*buttontext).setText(QString::number(0.1f * (float)((int)(10.0f * toolwidth))));
    }
    else if(tooltype == SGToolTypeEnum::CompleteEraser || tooltype == SGToolTypeEnum::PartialEraser || tooltype == SGToolTypeEnum::HighlighterCompleteEraser || tooltype == SGToolTypeEnum::HighlighterPartialEraser){
        if(tooltype == SGToolTypeEnum::CompleteEraser){(*buttonicon).setText("\uE01D");}
        else if(tooltype == SGToolTypeEnum::PartialEraser){(*buttonicon).setText("\uE01E");}
        else if(tooltype == SGToolTypeEnum::HighlighterCompleteEraser){(*buttonicon).setText("\uE01F");}
        else if(tooltype == SGToolTypeEnum::HighlighterPartialEraser){(*buttonicon).setText("\uE020");}
        SGGeneralLibrary::SetUIStyle(buttonicon, SGGeneralLibrary::stylesheetfieldtextcolour, SGCentralManagement::colour2);
        SGGeneralLibrary::SetUIStyle(buttonicon, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
        (*buttontext).show();
        (*buttontext).setText(QString::number(0.1f * (float)((int)(10.0f * toolwidth))));
    }
    else if(tooltype == SGToolTypeEnum::Highlighter){
        (*buttonicon).setText("\uE021");
        QString col = SGGeneralLibrary::ColourUintToCSS(toolcolour);
        SGGeneralLibrary::SetUIStyle(buttonicon, SGGeneralLibrary::stylesheetfieldtextcolour, col);
        SGGeneralLibrary::SetUIStyle(buttonicon, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
        (*buttontext).show();
        (*buttontext).setText(QString::number(0.1f * (float)((int)(10.0f * toolwidth))));
    }
    else if(tooltype == SGToolTypeEnum::PenStrokeSelector){
        (*buttonicon).setText("\uE025");
        SGGeneralLibrary::SetUIStyle(buttonicon, SGGeneralLibrary::stylesheetfieldtextcolour, SGCentralManagement::colour2);
        SGGeneralLibrary::SetUIStyle(buttonicon, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
        (*buttontext).hide();
    }
}

void SGFavouriteToolButton::setfavourite(){
    SGNoteViewManagement::deleteselectors();
    if(SGFavouriteToolsManagement::isdeleting == false){
        SGCentralManagement::activetooltype = tooltype;
        SGCentralManagement::activetoolcolour = toolcolour;
        SGCentralManagement::activetoolwidth = toolwidth;
        SGToolOptionsManagement::updatechangetoolicon();
    }
    else{
        for(int j=index+1; j<(*(*SGNoteViewManagement::favouritetoolslayout).objlist).size(); j++){
            (*(*SGNoteViewManagement::favouritetoolslayout).objlist)[j-1] = (*(*SGNoteViewManagement::favouritetoolslayout).objlist)[j];
            (*(SGFavouriteToolButton*)(*(*SGNoteViewManagement::favouritetoolslayout).objlist)[j-1]).index--;
        }
        (*(*SGNoteViewManagement::favouritetoolslayout).objlist).pop_back();
        (*SGNoteViewManagement::favouritetoolslayout).ReceiveUpdateCall();
        delete this;
        SGFavouriteToolsManagement::savefavouritetools();
    }
}

void SGFavouriteToolButton::ResizeObj(){
    SGWidget000110001::ResizeObj();
    (*buttonbackground).ResizeObj();
    (*buttonicon).ResizeObj();
    (*buttontext).ResizeObj();
}
