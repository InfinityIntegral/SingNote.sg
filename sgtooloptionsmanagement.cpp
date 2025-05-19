#include "sgtooloptionsmanagement.h"
#include "sgcentralmanagement.h"
#include "sgnoteviewmanagement.h"
#include "sgtooltypeenum.h"
#include "sggenerallibrary.h"
#include "sgnotemanagement.h"

SGWidget000221104* SGToolOptionsManagement::changetoolbackground = nullptr;
SGTextButton022211332* SGToolOptionsManagement::changetoolcancelbutton = nullptr;
SGTextButton022211232* SGToolOptionsManagement::changetoolmovebutton = nullptr;
SGTextButton022211232* SGToolOptionsManagement::changetoolpenbutton = nullptr;
SGTextButton022211232* SGToolOptionsManagement::changetoolhighlighterbutton = nullptr;
SGTextButton022211232* SGToolOptionsManagement::changetooleraserbutton = nullptr;
SGTextButton022211232* SGToolOptionsManagement::changetoolselectorbutton = nullptr;
SGTextButton022211232* SGToolOptionsManagement::changetoolshapebutton = nullptr;
SGTextButton022211232* SGToolOptionsManagement::changetoollaserpenbutton = nullptr;
SGTextButton022211232* SGToolOptionsManagement::changetoollaserpointerbutton = nullptr;
SGWidget000221103* SGToolOptionsManagement::changepenbackground = nullptr;
SGTextButton022314332* SGToolOptionsManagement::changepencancelbutton = nullptr;
SGTextButton022314332* SGToolOptionsManagement::changepenconfirmbutton = nullptr;
SGScrollView000231100* SGToolOptionsManagement::changepenscrollview = nullptr;
SGLayoutChangePen* SGToolOptionsManagement::changepenlayout = nullptr;
SGText012110021* SGToolOptionsManagement::changepentitletext = nullptr;
SGText012110021* SGToolOptionsManagement::changepencolourtext = nullptr;
SGInputField122110032* SGToolOptionsManagement::changepenredinput = nullptr;
SGInputField122110032* SGToolOptionsManagement::changepengreeninput = nullptr;
SGInputField122110032* SGToolOptionsManagement::changepenblueinput = nullptr;
SGText012110021* SGToolOptionsManagement::changepenwidthtext = nullptr;
SGInputField222110032* SGToolOptionsManagement::changepenwidthinput = nullptr;
SGWidget000221103* SGToolOptionsManagement::changeeraserbackground = nullptr;
SGTextButton022314332* SGToolOptionsManagement::changeerasercancelbutton = nullptr;
SGTextButton022314332* SGToolOptionsManagement::changeeraserconfirmbutton = nullptr;
SGScrollView000231100* SGToolOptionsManagement::changeeraserscrollview = nullptr;
SGLayoutChangeEraser* SGToolOptionsManagement::changeeraserlayout = nullptr;
SGText012110021* SGToolOptionsManagement::changeerasertitletext = nullptr;
SGText012110021* SGToolOptionsManagement::changeeraserwidthtext = nullptr;
SGInputField222110032* SGToolOptionsManagement::changeeraserwidthinput = nullptr;
SGTextButton022110032* SGToolOptionsManagement::changeerasercompletebutton = nullptr;
SGTextButton022110032* SGToolOptionsManagement::changeeraserpartialbutton = nullptr;
SGTextButton022110032* SGToolOptionsManagement::changeeraserhighlighterbutton = nullptr;
SGTextButton022110032* SGToolOptionsManagement::changeerasereverythingbutton = nullptr;
int SGToolOptionsManagement::tooltypeindicator = 0;
SGWidget000221103* SGToolOptionsManagement::changehighlighterbackground = nullptr;
SGTextButton022314332* SGToolOptionsManagement::changehighlightercancelbutton = nullptr;
SGTextButton022314332* SGToolOptionsManagement::changehighlighterconfirmbutton = nullptr;
SGScrollView000231100* SGToolOptionsManagement::changehighlighterscrollview = nullptr;
SGLayoutChangeHighlighter* SGToolOptionsManagement::changehighlighterlayout = nullptr;
SGText012110021* SGToolOptionsManagement::changehighlightertitletext = nullptr;
SGText012110021* SGToolOptionsManagement::changehighlightercolourtext = nullptr;
SGInputField122110032* SGToolOptionsManagement::changehighlighterredinput = nullptr;
SGInputField122110032* SGToolOptionsManagement::changehighlightergreeninput = nullptr;
SGInputField122110032* SGToolOptionsManagement::changehighlighterblueinput = nullptr;
SGInputField122110032* SGToolOptionsManagement::changehighlightertransparencyinput = nullptr;
SGText012110021* SGToolOptionsManagement::changehighlighterwidthtext = nullptr;
SGInputField222110032* SGToolOptionsManagement::changehighlighterwidthinput = nullptr;
SGWidget000221103* SGToolOptionsManagement::changeselectorbackground = nullptr;
SGTextButton022314332* SGToolOptionsManagement::changeselectorcancelbutton = nullptr;
SGTextButton022314332* SGToolOptionsManagement::changeselectorconfirmbutton = nullptr;
SGScrollView000231100* SGToolOptionsManagement::changeselectorscrollview = nullptr;
SGLayoutChangeSelector* SGToolOptionsManagement::changeselectorlayout = nullptr;
SGText012110021* SGToolOptionsManagement::changeselectortitletext = nullptr;
SGTextButton022110032* SGToolOptionsManagement::changeselectorpenstrokebutton = nullptr;
SGTextButton022110032* SGToolOptionsManagement::changeselectorboxbutton = nullptr;
SGTextButton022110032* SGToolOptionsManagement::changeselectorglobalbutton = nullptr;
SGTextButton022110032* SGToolOptionsManagement::changeselectorshapebutton = nullptr;

void SGToolOptionsManagement::showtooloptions(){
    SGNoteViewManagement::deleteselectors();
    SGToolOptionsManagement::tooltypeindicator = 0;
    (*SGNoteViewManagement::noteviewbackground).hide();
    if(SGToolOptionsManagement::changetoolbackground != nullptr){
        (*SGToolOptionsManagement::changetoolbackground).show();
        emit (*SGCentralManagement::signalsemitter).updatechangetoolsmenu();
        return;
    }
    SGToolOptionsManagement::changetoolbackground = new SGWidget000221104(SGCentralManagement::mainbackground, 0.0f, 0.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangetoolsmenu, SGToolOptionsManagement::changetoolbackground, &SGWidget000221104::ResizeObj);
    SGToolOptionsManagement::changetoolcancelbutton = new SGTextButton022211332(SGToolOptionsManagement::changetoolbackground, "cancel", 0.0f, 1.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangetoolsmenu, SGToolOptionsManagement::changetoolcancelbutton, &SGTextButton022211332::ResizeObj);
    connect(SGToolOptionsManagement::changetoolcancelbutton, &SGTextButton022211332::clicked, &SGToolOptionsManagement::changetoolcancel);
    SGToolOptionsManagement::changetoolmovebutton = new SGTextButton022211232(SGToolOptionsManagement::changetoolbackground, "move", 0.0f, -4.0f, 1.0f);
    connect(SGToolOptionsManagement::changetoolmovebutton, &SGTextButton022211232::clicked, &SGToolOptionsManagement::changetoolmove);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangetoolsmenu, SGToolOptionsManagement::changetoolmovebutton, &SGTextButton022211232::ResizeObj);
    SGToolOptionsManagement::changetoolpenbutton = new SGTextButton022211232(SGToolOptionsManagement::changetoolbackground, "pen", 0.0f, -3.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangetoolsmenu, SGToolOptionsManagement::changetoolpenbutton, &SGTextButton022211232::ResizeObj);
    connect(SGToolOptionsManagement::changetoolpenbutton, &SGTextButton022211232::clicked, &SGToolOptionsManagement::showchangepen);
    SGToolOptionsManagement::changetoolhighlighterbutton = new SGTextButton022211232(SGToolOptionsManagement::changetoolbackground, "highlighter", 0.0f, -2.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangetoolsmenu, SGToolOptionsManagement::changetoolhighlighterbutton, &SGTextButton022211232::ResizeObj);
    connect(SGToolOptionsManagement::changetoolhighlighterbutton, &SGTextButton022211232::clicked, &SGToolOptionsManagement::showchangehighlighter);
    SGToolOptionsManagement::changetooleraserbutton = new SGTextButton022211232(SGToolOptionsManagement::changetoolbackground, "eraser", 0.0f, -1.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangetoolsmenu, SGToolOptionsManagement::changetooleraserbutton, &SGTextButton022211232::ResizeObj);
    connect(SGToolOptionsManagement::changetooleraserbutton, &SGTextButton022211232::clicked, &SGToolOptionsManagement::showchangeeraser);
    SGToolOptionsManagement::changetoolselectorbutton = new SGTextButton022211232(SGToolOptionsManagement::changetoolbackground, "selector", 0.0f, 0.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangetoolsmenu, SGToolOptionsManagement::changetoolselectorbutton, &SGTextButton022211232::ResizeObj);
    connect(SGToolOptionsManagement::changetoolselectorbutton, &SGTextButton022211232::clicked, &SGToolOptionsManagement::showchangeselector);
    SGToolOptionsManagement::changetoolshapebutton = new SGTextButton022211232(SGToolOptionsManagement::changetoolbackground, "shapes", 0.0f, 1.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangetoolsmenu, SGToolOptionsManagement::changetoolshapebutton, &SGTextButton022211232::ResizeObj);
    SGToolOptionsManagement::changetoollaserpenbutton = new SGTextButton022211232(SGToolOptionsManagement::changetoolbackground, "laser pen", 0.0f, 2.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangetoolsmenu, SGToolOptionsManagement::changetoollaserpenbutton, &SGTextButton022211232::ResizeObj);
    SGToolOptionsManagement::changetoollaserpointerbutton = new SGTextButton022211232(SGToolOptionsManagement::changetoolbackground, "laser pointer", 0.0f, 3.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangetoolsmenu, SGToolOptionsManagement::changetoollaserpointerbutton, &SGTextButton022211232::ResizeObj);
}

void SGToolOptionsManagement::changetoolcancel(){
    (*SGToolOptionsManagement::changetoolbackground).hide();
    (*SGNoteViewManagement::noteviewbackground).show();
    emit (*SGCentralManagement::signalsemitter).updatenoteview();
}

void SGToolOptionsManagement::updatechangetoolicon(){
    (*SGNoteViewManagement::changetoolbutton).tooltype = SGCentralManagement::activetooltype;
    (*SGNoteViewManagement::changetoolbutton).toolcolour = SGCentralManagement::activetoolcolour;
    (*SGNoteViewManagement::changetoolbutton).toolwidth = SGCentralManagement::activetoolwidth;
    (*SGNoteViewManagement::changetoolbutton).refreshicon();
}

void SGToolOptionsManagement::changetoolmove(){
    SGCentralManagement::activetooltype = SGToolTypeEnum::Move;
    SGToolOptionsManagement::updatechangetoolicon();
    SGToolOptionsManagement::changetoolcancel();
}

void SGToolOptionsManagement::showchangepen(){
    if(SGToolOptionsManagement::changepenbackground != nullptr){
        (*SGToolOptionsManagement::changepenbackground).show();
        emit (*SGCentralManagement::signalsemitter).updatechangepenmenu();
        (*SGToolOptionsManagement::changepenredinput).setText("r");
        (*SGToolOptionsManagement::changepengreeninput).setText("g");
        (*SGToolOptionsManagement::changepenblueinput).setText("b");
        (*SGToolOptionsManagement::changepenwidthinput).setText("");
        return;
    }
    SGToolOptionsManagement::changepenbackground = new SGWidget000221103(SGCentralManagement::mainbackground, 0.0f, 0.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangepenmenu, SGToolOptionsManagement::changepenbackground, &SGWidget000221103::ResizeObj);
    SGToolOptionsManagement::changepencancelbutton = new SGTextButton022314332(SGToolOptionsManagement::changepenbackground, "cancel", 0.0f, 0.0f, 1.0f, 0.5f, 0.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangepenmenu, SGToolOptionsManagement::changepencancelbutton, &SGTextButton022314332::ResizeObj);
    connect(SGToolOptionsManagement::changepencancelbutton, &SGTextButton022314332::clicked, &SGToolOptionsManagement::changepencancel);
    SGToolOptionsManagement::changepenconfirmbutton = new SGTextButton022314332(SGToolOptionsManagement::changepenbackground, "confirm", 0.5f, 0.0f, 1.0f, 0.5f, 0.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangepenmenu, SGToolOptionsManagement::changepenconfirmbutton, &SGTextButton022314332::ResizeObj);
    connect(SGToolOptionsManagement::changepenconfirmbutton, &SGTextButton022314332::clicked, &SGToolOptionsManagement::changepenconfirm);
    SGToolOptionsManagement::changepenscrollview = new SGScrollView000231100(SGToolOptionsManagement::changepenbackground, 0.0f, 0.0f, 1.0f, -1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangepenmenu, SGToolOptionsManagement::changepenscrollview, &SGScrollView000231100::ResizeObj);
    SGToolOptionsManagement::changepenlayout = new SGLayoutChangePen(SGToolOptionsManagement::changepenscrollview);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangepenmenu, SGToolOptionsManagement::changepenlayout, &SGLayoutChangePen::ReceiveUpdateCall);
    (*SGToolOptionsManagement::changepenscrollview).setWidget(SGToolOptionsManagement::changepenlayout);
    (*SGToolOptionsManagement::changepenlayout).ReceiveUpdateCall();

    SGToolOptionsManagement::changepentitletext = new SGText012110021(SGToolOptionsManagement::changepenlayout, "customise pen...", 5.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangepenmenu, SGToolOptionsManagement::changepentitletext, &SGText012110021::ResizeObj);
    SGToolOptionsManagement::changepencolourtext = new SGText012110021(SGToolOptionsManagement::changepenlayout, "colour:", 2.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangepenmenu, SGToolOptionsManagement::changepencolourtext, &SGText012110021::ResizeObj);
    SGToolOptionsManagement::changepenredinput = new SGInputField122110032(SGToolOptionsManagement::changepenlayout, 2.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangepenmenu, SGToolOptionsManagement::changepenredinput, &SGInputField122110032::ResizeObj);
    (*SGToolOptionsManagement::changepenredinput).setText("r");
    SGToolOptionsManagement::changepengreeninput = new SGInputField122110032(SGToolOptionsManagement::changepenlayout, 2.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangepenmenu, SGToolOptionsManagement::changepengreeninput, &SGInputField122110032::ResizeObj);
    (*SGToolOptionsManagement::changepengreeninput).setText("g");
    SGToolOptionsManagement::changepenblueinput = new SGInputField122110032(SGToolOptionsManagement::changepenlayout, 2.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangepenmenu, SGToolOptionsManagement::changepenblueinput, &SGInputField122110032::ResizeObj);
    (*SGToolOptionsManagement::changepenblueinput).setText("b");
    SGToolOptionsManagement::changepenwidthtext = new SGText012110021(SGToolOptionsManagement::changepenlayout, "width:", 2.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangepenmenu, SGToolOptionsManagement::changepenwidthtext, &SGText012110021::ResizeObj);
    SGToolOptionsManagement::changepenwidthinput = new SGInputField222110032(SGToolOptionsManagement::changepenlayout, 4.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangepenmenu, SGToolOptionsManagement::changepenwidthinput, &SGInputField222110032::ResizeObj);
}

void SGToolOptionsManagement::changepencancel(){
    (*SGToolOptionsManagement::changepenbackground).hide();
    SGToolOptionsManagement::changetoolcancel();
}

void SGToolOptionsManagement::changepenconfirm(){
    bool x = false;
    bool c = true;
    float w = (*SGToolOptionsManagement::changepenwidthinput).text().toFloat(&x);
    if(w <= 0.0f){x = false;}
    if(x == false){
        (*SGToolOptionsManagement::changepenwidthinput).setText("");
        (*SGToolOptionsManagement::changepenwidthinput).setinvalid();
        c = false;
    }
    uint r = (*SGToolOptionsManagement::changepenredinput).text().toUInt(&x);
    if(r > 255){x = false;}
    if(x == false){
        (*SGToolOptionsManagement::changepenredinput).setText("r");
        (*SGToolOptionsManagement::changepenredinput).setinvalid();
        c = false;
    }
    uint g = (*SGToolOptionsManagement::changepengreeninput).text().toUInt(&x);
    if(g > 255){x = false;}
    if(x == false){
        (*SGToolOptionsManagement::changepengreeninput).setText("g");
        (*SGToolOptionsManagement::changepengreeninput).setinvalid();
        c = false;
    }
    uint b = (*SGToolOptionsManagement::changepenblueinput).text().toUInt(&x);
    if(b > 255){x = false;}
    if(x == false){
        (*SGToolOptionsManagement::changepenblueinput).setText("b");
        (*SGToolOptionsManagement::changepenblueinput).setinvalid();
        c = false;
    }
    if(c == false){return;}
    SGCentralManagement::activetooltype = SGToolTypeEnum::Pen;
    SGNoteManagement::penstrokezindex++;
    SGCentralManagement::activetoolwidth = w;
    SGCentralManagement::activetoolcolour = (r << 24) + (g << 16) + (b << 8) + 0xFF;
    (*SGToolOptionsManagement::changepenbackground).hide();
    SGToolOptionsManagement::updatechangetoolicon();
    SGToolOptionsManagement::changetoolcancel();
}

void SGToolOptionsManagement::showchangeeraser(){
    if(SGToolOptionsManagement::changeeraserbackground != nullptr){
        (*SGToolOptionsManagement::changeeraserbackground).show();
        emit (*SGCentralManagement::signalsemitter).updatechangeerasermenu();
        (*SGToolOptionsManagement::changeeraserwidthinput).setText("");
        SGToolOptionsManagement::changeerasercomplete();
        SGToolOptionsManagement::changeerasereverything();
        return;
    }

    SGToolOptionsManagement::changeeraserbackground = new SGWidget000221103(SGCentralManagement::mainbackground, 0.0f, 0.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangeerasermenu, SGToolOptionsManagement::changeeraserbackground, &SGWidget000221103::ResizeObj);
    SGToolOptionsManagement::changeerasercancelbutton = new SGTextButton022314332(SGToolOptionsManagement::changeeraserbackground, "cancel", 0.0f, 0.0f, 1.0f, 0.5f, 0.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangeerasermenu, SGToolOptionsManagement::changeerasercancelbutton, &SGTextButton022314332::ResizeObj);
    connect(SGToolOptionsManagement::changeerasercancelbutton, &SGTextButton022314332::clicked, &SGToolOptionsManagement::changeerasercancel);
    SGToolOptionsManagement::changeeraserconfirmbutton = new SGTextButton022314332(SGToolOptionsManagement::changeeraserbackground, "confirm", 0.5f, 0.0f, 1.0f, 0.5f, 0.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangeerasermenu, SGToolOptionsManagement::changeeraserconfirmbutton, &SGTextButton022314332::ResizeObj);
    connect(SGToolOptionsManagement::changeeraserconfirmbutton, &SGTextButton022314332::clicked, &SGToolOptionsManagement::changeeraserconfirm);
    SGToolOptionsManagement::changeeraserscrollview = new SGScrollView000231100(SGToolOptionsManagement::changeeraserbackground, 0.0f, 0.0f, 1.0f, -1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangeerasermenu, SGToolOptionsManagement::changeeraserscrollview, &SGScrollView000231100::ResizeObj);
    SGToolOptionsManagement::changeeraserlayout = new SGLayoutChangeEraser(SGToolOptionsManagement::changeeraserscrollview);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangeerasermenu, SGToolOptionsManagement::changeeraserlayout, &SGLayoutChangeEraser::ReceiveUpdateCall);
    (*SGToolOptionsManagement::changeeraserscrollview).setWidget(SGToolOptionsManagement::changeeraserlayout);
    (*SGToolOptionsManagement::changeeraserlayout).ReceiveUpdateCall();

    SGToolOptionsManagement::changeerasertitletext = new SGText012110021(SGToolOptionsManagement::changeeraserlayout, "customise eraser...", 5.5f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangeerasermenu, SGToolOptionsManagement::changeerasertitletext, &SGText012110021::ResizeObj);
    SGToolOptionsManagement::changeeraserwidthtext = new SGText012110021(SGToolOptionsManagement::changeeraserlayout, "width:", 2.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangeerasermenu, SGToolOptionsManagement::changeeraserwidthtext, &SGText012110021::ResizeObj);
    SGToolOptionsManagement::changeeraserwidthinput = new SGInputField222110032(SGToolOptionsManagement::changeeraserlayout, 4.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangeerasermenu, SGToolOptionsManagement::changeeraserwidthinput, &SGInputField222110032::ResizeObj);

    SGToolOptionsManagement::changeerasercompletebutton = new SGTextButton022110032(SGToolOptionsManagement::changeeraserlayout, "complete eraser", 5.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangeerasermenu, SGToolOptionsManagement::changeerasercompletebutton, &SGTextButton022110032::ResizeObj);
    connect(SGToolOptionsManagement::changeerasercompletebutton, &SGTextButton022110032::clicked, &SGToolOptionsManagement::changeerasercomplete);
    SGToolOptionsManagement::changeeraserpartialbutton = new SGTextButton022110032(SGToolOptionsManagement::changeeraserlayout, "partial eraser", 5.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangeerasermenu, SGToolOptionsManagement::changeeraserpartialbutton, &SGTextButton022110032::ResizeObj);
    connect(SGToolOptionsManagement::changeeraserpartialbutton, &SGTextButton022110032::clicked, &SGToolOptionsManagement::changeeraserpartial);
    SGToolOptionsManagement::changeerasereverythingbutton = new SGTextButton022110032(SGToolOptionsManagement::changeeraserlayout, "erase everything", 6.5f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangeerasermenu, SGToolOptionsManagement::changeerasereverythingbutton, &SGTextButton022110032::ResizeObj);
    connect(SGToolOptionsManagement::changeerasereverythingbutton, &SGTextButton022110032::clicked, &SGToolOptionsManagement::changeerasereverything);
    SGToolOptionsManagement::changeeraserhighlighterbutton = new SGTextButton022110032(SGToolOptionsManagement::changeeraserlayout, "erase only highlighter", 6.5f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangeerasermenu, SGToolOptionsManagement::changeeraserhighlighterbutton, &SGTextButton022110032::ResizeObj);
    connect(SGToolOptionsManagement::changeeraserhighlighterbutton, &SGTextButton022110032::clicked, &SGToolOptionsManagement::changeeraserhighlighter);

    SGToolOptionsManagement::changeerasercomplete();
    SGToolOptionsManagement::changeerasereverything();
}

void SGToolOptionsManagement::changeerasercancel(){
    (*SGToolOptionsManagement::changeeraserbackground).hide();
    SGToolOptionsManagement::changetoolcancel();
}

void SGToolOptionsManagement::changeerasercomplete(){
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeerasercompletebutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeeraserpartialbutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    if(SGToolOptionsManagement::tooltypeindicator == 1){SGToolOptionsManagement::tooltypeindicator = 0;}
    else if(SGToolOptionsManagement::tooltypeindicator == 3){SGToolOptionsManagement::tooltypeindicator = 2;}
}

void SGToolOptionsManagement::changeeraserpartial(){
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeerasercompletebutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeeraserpartialbutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
    if(SGToolOptionsManagement::tooltypeindicator == 0){SGToolOptionsManagement::tooltypeindicator = 1;}
    else if(SGToolOptionsManagement::tooltypeindicator == 2){SGToolOptionsManagement::tooltypeindicator = 3;}
}

void SGToolOptionsManagement::changeerasereverything(){
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeerasereverythingbutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeeraserhighlighterbutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    if(SGToolOptionsManagement::tooltypeindicator == 2){SGToolOptionsManagement::tooltypeindicator = 0;}
    else if(SGToolOptionsManagement::tooltypeindicator == 3){SGToolOptionsManagement::tooltypeindicator = 1;}
}

void SGToolOptionsManagement::changeeraserhighlighter(){
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeerasereverythingbutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeeraserhighlighterbutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
    if(SGToolOptionsManagement::tooltypeindicator == 0){SGToolOptionsManagement::tooltypeindicator = 2;}
    else if(SGToolOptionsManagement::tooltypeindicator == 1){SGToolOptionsManagement::tooltypeindicator = 3;}
}

void SGToolOptionsManagement::changeeraserconfirm(){
    bool x = false;
    bool c = true;
    float w = (*SGToolOptionsManagement::changeeraserwidthinput).text().toFloat(&x);
    if(w <= 0.0f){x = false;}
    if(x == false){
        (*SGToolOptionsManagement::changeeraserwidthinput).setText("");
        (*SGToolOptionsManagement::changeeraserwidthinput).setinvalid();
        c = false;
    }
    if(c == false){return;}
    if(SGToolOptionsManagement::tooltypeindicator == 0){SGCentralManagement::activetooltype = SGToolTypeEnum::CompleteEraser;}
    else if(SGToolOptionsManagement::tooltypeindicator == 1){SGCentralManagement::activetooltype = SGToolTypeEnum::PartialEraser;}
    else if(SGToolOptionsManagement::tooltypeindicator == 2){SGCentralManagement::activetooltype = SGToolTypeEnum::HighlighterCompleteEraser;}
    else if(SGToolOptionsManagement::tooltypeindicator == 3){SGCentralManagement::activetooltype = SGToolTypeEnum::HighlighterPartialEraser;}
    SGCentralManagement::activetoolwidth = w;
    (*SGToolOptionsManagement::changeeraserbackground).hide();
    SGToolOptionsManagement::updatechangetoolicon();
    SGToolOptionsManagement::changetoolcancel();
}

void SGToolOptionsManagement::showchangehighlighter(){
    if(SGToolOptionsManagement::changehighlighterbackground != nullptr){
        (*SGToolOptionsManagement::changehighlighterbackground).show();
        emit (*SGCentralManagement::signalsemitter).updatechangehighlightermenu();
        (*SGToolOptionsManagement::changehighlighterredinput).setText("r");
        (*SGToolOptionsManagement::changehighlightergreeninput).setText("g");
        (*SGToolOptionsManagement::changehighlighterblueinput).setText("b");
        (*SGToolOptionsManagement::changehighlightertransparencyinput).setText("a");
        (*SGToolOptionsManagement::changehighlighterwidthinput).setText("");
        return;
    }

    SGToolOptionsManagement::changehighlighterbackground = new SGWidget000221103(SGCentralManagement::mainbackground, 0.0f, 0.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangehighlightermenu, SGToolOptionsManagement::changehighlighterbackground, &SGWidget000221103::ResizeObj);
    SGToolOptionsManagement::changehighlightercancelbutton = new SGTextButton022314332(SGToolOptionsManagement::changehighlighterbackground, "cancel", 0.0f, 0.0f, 1.0f, 0.5f, 0.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangehighlightermenu, SGToolOptionsManagement::changehighlightercancelbutton, &SGTextButton022314332::ResizeObj);
    connect(SGToolOptionsManagement::changehighlightercancelbutton, &SGTextButton022314332::clicked, &SGToolOptionsManagement::changehighlightercancel);
    SGToolOptionsManagement::changehighlighterconfirmbutton = new SGTextButton022314332(SGToolOptionsManagement::changehighlighterbackground, "confirm", 0.5f, 0.0f, 1.0f, 0.5f, 0.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangehighlightermenu, SGToolOptionsManagement::changehighlighterconfirmbutton, &SGTextButton022314332::ResizeObj);
    connect(SGToolOptionsManagement::changehighlighterconfirmbutton, &SGTextButton022314332::clicked, &SGToolOptionsManagement::changehighlighterconfirm);
    SGToolOptionsManagement::changehighlighterscrollview = new SGScrollView000231100(SGToolOptionsManagement::changehighlighterbackground, 0.0f, 0.0f, 1.0f, -1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangehighlightermenu, SGToolOptionsManagement::changehighlighterscrollview, &SGScrollView000231100::ResizeObj);
    SGToolOptionsManagement::changehighlighterlayout = new SGLayoutChangeHighlighter(SGToolOptionsManagement::changehighlighterbackground);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangehighlightermenu, SGToolOptionsManagement::changehighlighterlayout, &SGLayoutChangeHighlighter::ReceiveUpdateCall);
    (*SGToolOptionsManagement::changehighlighterscrollview).setWidget(SGToolOptionsManagement::changehighlighterlayout);
    (*SGToolOptionsManagement::changehighlighterlayout).ReceiveUpdateCall();

    SGToolOptionsManagement::changehighlightertitletext = new SGText012110021(SGToolOptionsManagement::changehighlighterlayout, "customise highlighter...", 7.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangehighlightermenu, SGToolOptionsManagement::changehighlightertitletext, &SGText012110021::ResizeObj);
    SGToolOptionsManagement::changehighlightercolourtext = new SGText012110021(SGToolOptionsManagement::changehighlighterlayout, "colour:", 2.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangehighlightermenu, SGToolOptionsManagement::changehighlightercolourtext, &SGText012110021::ResizeObj);
    SGToolOptionsManagement::changehighlighterredinput = new SGInputField122110032(SGToolOptionsManagement::changehighlighterlayout, 2.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangehighlightermenu, SGToolOptionsManagement::changehighlighterredinput, &SGInputField122110032::ResizeObj);
    (*SGToolOptionsManagement::changehighlighterredinput).setText("r");
    SGToolOptionsManagement::changehighlightergreeninput = new SGInputField122110032(SGToolOptionsManagement::changehighlighterlayout, 2.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangehighlightermenu, SGToolOptionsManagement::changehighlightergreeninput, &SGInputField122110032::ResizeObj);
    (*SGToolOptionsManagement::changehighlightergreeninput).setText("g");
    SGToolOptionsManagement::changehighlighterblueinput = new SGInputField122110032(SGToolOptionsManagement::changehighlighterlayout, 2.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangehighlightermenu, SGToolOptionsManagement::changehighlighterblueinput, &SGInputField122110032::ResizeObj);
    (*SGToolOptionsManagement::changehighlighterblueinput).setText("b");
    SGToolOptionsManagement::changehighlightertransparencyinput = new SGInputField122110032(SGToolOptionsManagement::changehighlighterlayout, 2.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangehighlightermenu, SGToolOptionsManagement::changehighlightertransparencyinput, &SGInputField122110032::ResizeObj);
    (*SGToolOptionsManagement::changehighlightertransparencyinput).setText("a");
    SGToolOptionsManagement::changehighlighterwidthtext = new SGText012110021(SGToolOptionsManagement::changehighlighterlayout, "width:", 2.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangehighlightermenu, SGToolOptionsManagement::changehighlighterwidthtext, &SGText012110021::ResizeObj);
    SGToolOptionsManagement::changehighlighterwidthinput = new SGInputField222110032(SGToolOptionsManagement::changehighlighterlayout, 4.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangehighlightermenu, SGToolOptionsManagement::changehighlighterwidthinput, &SGInputField222110032::ResizeObj);
}

void SGToolOptionsManagement::changehighlightercancel(){
    (*SGToolOptionsManagement::changehighlighterbackground).hide();
    SGToolOptionsManagement::changetoolcancel();
}

void SGToolOptionsManagement::changehighlighterconfirm(){
    bool x = false;
    bool c = true;
    float w = (*SGToolOptionsManagement::changehighlighterwidthinput).text().toFloat(&x);
    if(w <= 0.0f){x = false;}
    if(x == false){
        (*SGToolOptionsManagement::changehighlighterwidthinput).setText("");
        (*SGToolOptionsManagement::changehighlighterwidthinput).setinvalid();
        c = false;
    }
    uint r = (*SGToolOptionsManagement::changehighlighterredinput).text().toUInt(&x);
    if(r > 255){x = false;}
    if(x == false){
        (*SGToolOptionsManagement::changehighlighterredinput).setText("r");
        (*SGToolOptionsManagement::changehighlighterredinput).setinvalid();
        c = false;
    }
    uint g = (*SGToolOptionsManagement::changehighlightergreeninput).text().toUInt(&x);
    if(g > 255){x = false;}
    if(x == false){
        (*SGToolOptionsManagement::changehighlightergreeninput).setText("g");
        (*SGToolOptionsManagement::changehighlightergreeninput).setinvalid();
        c = false;
    }
    uint b = (*SGToolOptionsManagement::changehighlighterblueinput).text().toUInt(&x);
    if(b > 255){x = false;}
    if(x == false){
        (*SGToolOptionsManagement::changehighlighterblueinput).setText("b");
        (*SGToolOptionsManagement::changehighlighterblueinput).setinvalid();
        c = false;
    }
    uint a = (*SGToolOptionsManagement::changehighlightertransparencyinput).text().toUInt(&x);
    if(a > 255 || a < 1){x = false;}
    if(x == false){
        (*SGToolOptionsManagement::changehighlightertransparencyinput).setText("a");
        (*SGToolOptionsManagement::changehighlightertransparencyinput).setinvalid();
        c = false;
    }
    if(c == false){return;}
    SGCentralManagement::activetooltype = SGToolTypeEnum::Highlighter;
    SGNoteManagement::highlighterstrokezindex++;
    SGCentralManagement::activetoolwidth = w;
    SGCentralManagement::activetoolcolour = (r << 24) + (g << 16) + (b << 8) + a;
    (*SGToolOptionsManagement::changehighlighterbackground).hide();
    SGToolOptionsManagement::updatechangetoolicon();
    SGToolOptionsManagement::changetoolcancel();
}

void SGToolOptionsManagement::showchangeselector(){
    if(SGToolOptionsManagement::changeselectorbackground != nullptr){
        (*SGToolOptionsManagement::changeselectorbackground).show();
        emit (*SGCentralManagement::signalsemitter).updatechangeselectormenu();
        SGToolOptionsManagement::changeselectorpenstroke();
        return;
    }

    SGToolOptionsManagement::changeselectorbackground = new SGWidget000221103(SGCentralManagement::mainbackground, 0.0f, 0.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangeselectormenu, SGToolOptionsManagement::changeselectorbackground, &SGWidget000221103::ResizeObj);
    SGToolOptionsManagement::changeselectorcancelbutton = new SGTextButton022314332(SGToolOptionsManagement::changeselectorbackground, "cancel", 0.0f, 0.0f, 1.0f, 0.5f, 0.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangeselectormenu, SGToolOptionsManagement::changeselectorcancelbutton, &SGTextButton022314332::ResizeObj);
    connect(SGToolOptionsManagement::changeselectorcancelbutton, &SGTextButton022314332::clicked, &SGToolOptionsManagement::changeselectorcancel);
    SGToolOptionsManagement::changeselectorconfirmbutton = new SGTextButton022314332(SGToolOptionsManagement::changeselectorbackground, "confirm", 0.5f, 0.0f, 1.0f, 0.5f, 0.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangeselectormenu, SGToolOptionsManagement::changeselectorconfirmbutton, &SGTextButton022314332::ResizeObj);
    connect(SGToolOptionsManagement::changeselectorconfirmbutton, &SGTextButton022314332::clicked, &SGToolOptionsManagement::changeselectorconfirm);
    SGToolOptionsManagement::changeselectorscrollview = new SGScrollView000231100(SGToolOptionsManagement::changeselectorbackground, 0.0f, 0.0f, 1.0f, -1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangeselectormenu, SGToolOptionsManagement::changeselectorscrollview, &SGScrollView000231100::ResizeObj);
    SGToolOptionsManagement::changeselectorlayout = new SGLayoutChangeSelector(SGToolOptionsManagement::changeselectorscrollview);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangeselectormenu, SGToolOptionsManagement::changeselectorlayout, &SGLayoutChangeSelector::ReceiveUpdateCall);
    (*SGToolOptionsManagement::changeselectorscrollview).setWidget(SGToolOptionsManagement::changeselectorlayout);
    (*SGToolOptionsManagement::changeselectorlayout).ReceiveUpdateCall();

    SGToolOptionsManagement::changeselectortitletext = new SGText012110021(SGToolOptionsManagement::changeselectorlayout, "customise selector...", 6.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangeselectormenu, SGToolOptionsManagement::changeselectortitletext, &SGText012110021::ResizeObj);
    SGToolOptionsManagement::changeselectorpenstrokebutton = new SGTextButton022110032(SGToolOptionsManagement::changeselectorlayout, "edit pen / highlighter", 11.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangeselectormenu, SGToolOptionsManagement::changeselectorpenstrokebutton, &SGTextButton022110032::ResizeObj);
    connect(SGToolOptionsManagement::changeselectorpenstrokebutton, &SGTextButton022110032::clicked, &SGToolOptionsManagement::changeselectorpenstroke);
    SGToolOptionsManagement::changeselectorboxbutton = new SGTextButton022110032(SGToolOptionsManagement::changeselectorlayout, "edit box elements", 11.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangeselectormenu, SGToolOptionsManagement::changeselectorboxbutton, &SGTextButton022110032::ResizeObj);
    connect(SGToolOptionsManagement::changeselectorboxbutton, &SGTextButton022110032::clicked, &SGToolOptionsManagement::changeselectorbox);
    SGToolOptionsManagement::changeselectorglobalbutton = new SGTextButton022110032(SGToolOptionsManagement::changeselectorlayout, "copy / paste / delete / screenshot", 11.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangeselectormenu, SGToolOptionsManagement::changeselectorglobalbutton, &SGTextButton022110032::ResizeObj);
    connect(SGToolOptionsManagement::changeselectorglobalbutton, &SGTextButton022110032::clicked, &SGToolOptionsManagement::changeselectorglobal);
    SGToolOptionsManagement::changeselectorshapebutton = new SGTextButton022110032(SGToolOptionsManagement::changeselectorlayout, "edit shape", 11.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatechangeselectormenu, SGToolOptionsManagement::changeselectorshapebutton, &SGTextButton022110032::ResizeObj);
    connect(SGToolOptionsManagement::changeselectorshapebutton, &SGTextButton022110032::clicked, &SGToolOptionsManagement::changeselectorshape);
    SGToolOptionsManagement::changeselectorpenstroke();
}

void SGToolOptionsManagement::changeselectorcancel(){
    (*SGToolOptionsManagement::changeselectorbackground).hide();
    SGToolOptionsManagement::changetoolcancel();
}

void SGToolOptionsManagement::changeselectorconfirm(){
    if(SGToolOptionsManagement::tooltypeindicator == 0){SGCentralManagement::activetooltype = SGToolTypeEnum::PenStrokeSelector;}
    else if(SGToolOptionsManagement::tooltypeindicator == 1){SGCentralManagement::activetooltype = SGToolTypeEnum::BoxSelector;}
    else if(SGToolOptionsManagement::tooltypeindicator == 2){SGCentralManagement::activetooltype = SGToolTypeEnum::GlobalSelector;}
    else if(SGToolOptionsManagement::tooltypeindicator == 3){SGCentralManagement::activetooltype = SGToolTypeEnum::ShapeSelector;}
    (*SGToolOptionsManagement::changeselectorbackground).hide();
    SGToolOptionsManagement::updatechangetoolicon();
    SGToolOptionsManagement::changetoolcancel();
}

void SGToolOptionsManagement::changeselectorpenstroke(){
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeselectorpenstrokebutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeselectorboxbutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeselectorglobalbutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeselectorshapebutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    SGToolOptionsManagement::tooltypeindicator = 0;
}

void SGToolOptionsManagement::changeselectorbox(){
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeselectorpenstrokebutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeselectorboxbutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeselectorglobalbutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeselectorshapebutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    SGToolOptionsManagement::tooltypeindicator = 1;
}

void SGToolOptionsManagement::changeselectorglobal(){
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeselectorpenstrokebutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeselectorboxbutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeselectorglobalbutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeselectorshapebutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    SGToolOptionsManagement::tooltypeindicator = 2;
}

void SGToolOptionsManagement::changeselectorshape(){
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeselectorpenstrokebutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeselectorboxbutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeselectorglobalbutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    SGGeneralLibrary::SetUIStyle(SGToolOptionsManagement::changeselectorshapebutton, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
    SGToolOptionsManagement::tooltypeindicator = 3;
}
