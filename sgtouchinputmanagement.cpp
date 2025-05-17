#include "sgtouchinputmanagement.h"
#include <QTimer>
#include "sgcentralmanagement.h"
#include "sgnoteinteractionmodeenum.h"
#include "sgviewportmanagement.h"
#include "sgnoteviewmanagement.h"
#include "sgnotequickmovemanagement.h"
#include "sgtooltypeenum.h"
#include "sgpenmanagement.h"
#include "sgerasermanagement.h"
#include "sghighlightermanagement.h"
#include "sgpenstrokeselectormanagement.h"

bool SGTouchInputManagement::scheduled = false;
QVector<SGTouchEvent>* SGTouchInputManagement::activetouches = nullptr;
SGTouchEvent SGTouchInputManagement::drawingtouch = SGTouchEvent(0, 0, false, 0.0f, 0.0f);
SGTouchEvent SGTouchInputManagement::scrolltouch1 = SGTouchEvent(0, 0, false, 0.0f, 0.0f);
SGTouchEvent SGTouchInputManagement::scrolltouch2 = SGTouchEvent(0, 0, false, 0.0f, 0.0f);
SGTouchEvent SGTouchInputManagement::selecttouch = SGTouchEvent(0, 0, false, 0.0f, 0.0f);
int SGTouchInputManagement::quickmovemode = 0;
float SGTouchInputManagement::quickmovex = 1.5f;
float SGTouchInputManagement::quickmovey = 1.5f;
QElapsedTimer* SGTouchInputManagement::quickmovetimer = nullptr;

void SGTouchInputManagement::processtouchfromqt(QTouchEvent* e){
    if(SGTouchInputManagement::activetouches == nullptr){SGTouchInputManagement::activetouches = new QVector<SGTouchEvent>();}
    QList<QTouchEvent::TouchPoint> tps = (*e).points();
    for(int i=0; i<tps.size(); i++){
        float x0 = tps[i].position().x();
        float y0 = tps[i].position().y();
        int id0 = tps[i].id();
        if(x0 < 0.0f || y0 < 0.0f || x0 > (*SGNoteViewManagement::renderarea).size().width() || y0 > (*SGNoteViewManagement::renderarea).size().height()){continue;}
        bool ispen0 = false; // add in touch type handling later
        int phase0 = 0;
        if(tps[i].state() == QEventPoint::Pressed){phase0 = SGTouchEvent::TouchStart;}
        else if(tps[i].state() == QEventPoint::Stationary || tps[i].state() == QEventPoint::Updated){phase0 = SGTouchEvent::TouchOngoing;}
        else{phase0 = SGTouchEvent::TouchEnd;}
        (*SGTouchInputManagement::activetouches).push_back(SGTouchEvent(id0, phase0, ispen0, x0, y0));
    }
    if(SGTouchInputManagement::scheduled == false){
        QTimer::singleShot(0, &SGTouchInputManagement::processtouchevents);
        SGTouchInputManagement::scheduled = true;
    }
}

void SGTouchInputManagement::processtouchevents(){
    bool lastframedraw = true;
    bool lastframescroll1 = true;
    bool lastframescroll2 = true;
    bool lastframeselect = true;
    if(SGTouchInputManagement::drawingtouch.id == 0){lastframedraw = false;}
    if(SGTouchInputManagement::scrolltouch1.id == 0){lastframescroll1 = false;}
    if(SGTouchInputManagement::scrolltouch2.id == 0){lastframescroll2 = false;}
    if(SGTouchInputManagement::selecttouch.id == 0){lastframeselect = false;}
    bool thisframedraw = false;
    bool thisframescroll1 = false;
    bool thisframescroll2 = false;
    bool thisframeselect = false;
    bool drawstartcall = false;
    bool drawongoingcall = false;
    bool drawendcall = false;
    bool scroll1startcall = false;
    bool scroll1ongoingcall = false;
    bool scroll1endcall = false;
    bool scroll2startcall = false;
    bool scroll2ongoingcall = false;
    bool scroll2endcall = false;
    bool selectstartcall = false;
    bool selectongoingcall = false;
    bool selectendcall = false;
    bool quickmoveendcall = false;
    for(int i=0; i<(*SGTouchInputManagement::activetouches).size(); i++){
        if((*SGTouchInputManagement::activetouches)[i].phase == SGTouchEvent::TouchStart){
            if(SGCentralManagement::interactionmode == SGNoteInteractionModeEnum::Normal){
                if((*SGTouchInputManagement::activetouches)[i].pen == false){
                    if(SGTouchInputManagement::scrolltouch1.id == 0){
                        SGTouchInputManagement::scrolltouch1 = (*SGTouchInputManagement::activetouches)[i];
                        thisframescroll1 = true;
                        scroll1startcall = true;
                    }
                    else if(SGTouchInputManagement::scrolltouch2.id == 0){
                        SGTouchInputManagement::scrolltouch2 = (*SGTouchInputManagement::activetouches)[i];
                        thisframescroll2 = true;
                        scroll2startcall = true;
                    }
                }
                else{
                    if(SGTouchInputManagement::drawingtouch.id == 0){
                        SGTouchInputManagement::drawingtouch = (*SGTouchInputManagement::activetouches)[i];
                        thisframedraw = true;
                        drawstartcall = true;
                    }
                }
            }
            else if(SGCentralManagement::interactionmode == SGNoteInteractionModeEnum::ScrollOnly){
                if(SGTouchInputManagement::scrolltouch1.id == 0){
                    SGTouchInputManagement::scrolltouch1 = (*SGTouchInputManagement::activetouches)[i];
                    thisframescroll1 = true;
                    scroll1startcall = true;
                }
                else if(SGTouchInputManagement::scrolltouch2.id == 0){
                    SGTouchInputManagement::scrolltouch2 = (*SGTouchInputManagement::activetouches)[i];
                    thisframescroll2 = true;
                    scroll2startcall = true;
                }
            }
            else{
                if(SGTouchInputManagement::drawingtouch.id == 0){
                    SGTouchInputManagement::drawingtouch = (*SGTouchInputManagement::activetouches)[i];
                    thisframedraw = true;
                    drawstartcall = true;
                }
            }
        }
        else if((*SGTouchInputManagement::activetouches)[i].phase == SGTouchEvent::TouchOngoing){
            if(SGTouchInputManagement::drawingtouch.id == (*SGTouchInputManagement::activetouches)[i].id){
                SGTouchInputManagement::drawingtouch = (*SGTouchInputManagement::activetouches)[i];
                thisframedraw = true;
                drawongoingcall = true;
            }
            if(SGTouchInputManagement::scrolltouch1.id == (*SGTouchInputManagement::activetouches)[i].id){
                SGTouchInputManagement::scrolltouch1 = (*SGTouchInputManagement::activetouches)[i];
                thisframescroll1 = true;
                scroll1ongoingcall = true;
            }
            if(SGTouchInputManagement::scrolltouch2.id == (*SGTouchInputManagement::activetouches)[i].id){
                SGTouchInputManagement::scrolltouch2 = (*SGTouchInputManagement::activetouches)[i];
                thisframescroll2 = true;
                scroll2ongoingcall = true;
            }
        }
        else if((*SGTouchInputManagement::activetouches)[i].phase == SGTouchEvent::TouchEnd){
            if(SGTouchInputManagement::drawingtouch.id == (*SGTouchInputManagement::activetouches)[i].id){thisframedraw = false;}
            if(SGTouchInputManagement::scrolltouch1.id == (*SGTouchInputManagement::activetouches)[i].id){thisframescroll1 = false;}
            if(SGTouchInputManagement::scrolltouch2.id == (*SGTouchInputManagement::activetouches)[i].id){thisframescroll2 = false;}
        }
    }
    if(thisframedraw == false){
        SGTouchInputManagement::drawingtouch = SGTouchEvent(0, 0, false, SGTouchInputManagement::drawingtouch.x, SGTouchInputManagement::drawingtouch.y);
        if(lastframedraw == true){drawendcall = true;}
    }
    if(thisframescroll1 == false){
        SGTouchInputManagement::scrolltouch1 = SGTouchEvent(0, 0, false, SGTouchInputManagement::scrolltouch1.x, SGTouchInputManagement::scrolltouch1.y);
        if(lastframescroll1 == true){scroll1endcall = true;}
    }
    if(thisframescroll2 == false){
        SGTouchInputManagement::scrolltouch2 = SGTouchEvent(0, 0, false, SGTouchInputManagement::scrolltouch2.x, SGTouchInputManagement::scrolltouch2.y);
        if(lastframescroll2 == true){scroll2endcall = true;}
    }
    if(SGTouchInputManagement::selecttouch.id == 0){
        if(SGTouchInputManagement::drawingtouch.id != 0 && SGTouchInputManagement::drawingtouch.phase == SGTouchEvent::TouchStart){
            SGTouchInputManagement::selecttouch = SGTouchInputManagement::drawingtouch;
            thisframeselect = true;
            selectstartcall = true;
            SGTouchInputManagement::quickmovestart();
            SGTouchInputManagement::quickmoveongoing();
        }
        else if(SGTouchInputManagement::scrolltouch1.id != 0 && SGTouchInputManagement::scrolltouch1.phase == SGTouchEvent::TouchStart){
            SGTouchInputManagement::selecttouch = SGTouchInputManagement::scrolltouch1;
            thisframeselect = true;
            selectstartcall = true;
            SGTouchInputManagement::quickmovestart();
            SGTouchInputManagement::quickmoveongoing();
        }
        else if(SGTouchInputManagement::scrolltouch2.id != 0 && SGTouchInputManagement::scrolltouch2.phase == SGTouchEvent::TouchStart){
            SGTouchInputManagement::selecttouch = SGTouchInputManagement::scrolltouch2;
            thisframeselect = true;
            selectstartcall = true;
            SGTouchInputManagement::quickmovestart();
            SGTouchInputManagement::quickmoveongoing();
        }
    }
    else{
        if(SGTouchInputManagement::drawingtouch.id == SGTouchInputManagement::selecttouch.id && SGTouchInputManagement::drawingtouch.phase == SGTouchEvent::TouchOngoing){
            SGTouchInputManagement::selecttouch = SGTouchInputManagement::drawingtouch;
            thisframeselect = true;
            selectongoingcall = true;
            SGTouchInputManagement::quickmoveongoing();
        }
        else if(SGTouchInputManagement::scrolltouch1.id == SGTouchInputManagement::selecttouch.id && SGTouchInputManagement::scrolltouch1.phase == SGTouchEvent::TouchOngoing){
            SGTouchInputManagement::selecttouch = SGTouchInputManagement::scrolltouch1;
            thisframeselect = true;
            selectongoingcall = true;
            SGTouchInputManagement::quickmoveongoing();
        }
        else if(SGTouchInputManagement::scrolltouch2.id == SGTouchInputManagement::selecttouch.id && SGTouchInputManagement::scrolltouch2.phase == SGTouchEvent::TouchOngoing){
            SGTouchInputManagement::selecttouch = SGTouchInputManagement::scrolltouch2;
            thisframeselect = true;
            selectongoingcall = true;
            SGTouchInputManagement::quickmoveongoing();
        }
    }
    if(thisframeselect == false){
        SGTouchInputManagement::selecttouch = SGTouchEvent(0, 0, false, SGTouchInputManagement::selecttouch.x, SGTouchInputManagement::selecttouch.y);
        if(lastframeselect == true){
            selectendcall = true;
            quickmoveendcall = true;
        }
    }
    if(SGTouchInputManagement::quickmovemode == 0){
        if(scroll1startcall){
            SGTouchInputManagement::scroll1start();
            SGTouchInputManagement::scroll1ongoing();
        }
        else if(scroll1endcall){
            SGTouchInputManagement::scroll1ongoing();
            SGTouchInputManagement::scroll1end();
        }
        else if(scroll1ongoingcall){SGTouchInputManagement::scroll1ongoing();}

        if(scroll2startcall){
            SGTouchInputManagement::scroll2start();
            SGTouchInputManagement::scroll2ongoing();
        }
        else if(scroll2endcall){
            SGTouchInputManagement::scroll2ongoing();
            SGTouchInputManagement::scroll2end();
        }
        else if(scroll2ongoingcall){SGTouchInputManagement::scroll2ongoing();}

        if(drawstartcall){
            SGTouchInputManagement::drawstart();
            SGTouchInputManagement::drawongoing();
        }
        else if(drawendcall){
            SGTouchInputManagement::drawongoing();
            SGTouchInputManagement::drawend();
        }
        else if(drawongoingcall){SGTouchInputManagement::drawongoing();}

        if(selectstartcall){
            SGTouchInputManagement::selectstart();
            SGTouchInputManagement::selectongoing();
        }
        else if(selectendcall){
            SGTouchInputManagement::selectongoing();
            SGTouchInputManagement::selectend();
        }
        else if(selectongoingcall){SGTouchInputManagement::selectongoing();}
    }
    if(quickmoveendcall){
        SGTouchInputManagement::quickmoveongoing();
        SGTouchInputManagement::quickmoveend();
    }
    SGTouchInputManagement::scheduled = false;
    delete SGTouchInputManagement::activetouches;
    SGTouchInputManagement::activetouches = nullptr;
}

void SGTouchInputManagement::drawstart(){
    if(SGCentralManagement::activetooltype == SGToolTypeEnum::Move){
        if(SGTouchInputManagement::scrolltouch1.id != 0){
            SGTouchInputManagement::scrolltouch2 = SGTouchEvent(0, 0, false, SGTouchInputManagement::scrolltouch1.x, SGTouchInputManagement::scrolltouch1.y);
            SGTouchInputManagement::scrolltouch1 = SGTouchEvent(0, 0, false, SGTouchInputManagement::drawingtouch.x, SGTouchInputManagement::drawingtouch.y);
            SGViewportManagement::zoomstart();
        }
        else{
            SGTouchInputManagement::scrolltouch1 = SGTouchEvent(0, 0, false, SGTouchInputManagement::drawingtouch.x, SGTouchInputManagement::drawingtouch.y);
            SGViewportManagement::movestart();
        }
    }
    else if(SGCentralManagement::activetooltype == SGToolTypeEnum::Pen){SGPenManagement::startnewpenstroke();}
    else if(SGCentralManagement::activetooltype == SGToolTypeEnum::CompleteEraser || SGCentralManagement::activetooltype == SGToolTypeEnum::PartialEraser || SGCentralManagement::activetooltype == SGToolTypeEnum::HighlighterCompleteEraser || SGCentralManagement::activetooltype == SGToolTypeEnum::HighlighterPartialEraser){SGEraserManagement::createeraser();}
    else if(SGCentralManagement::activetooltype == SGToolTypeEnum::Highlighter){SGHighlighterManagement::startnewhighlighterstroke();}
    else if(SGCentralManagement::activetooltype == SGToolTypeEnum::PenStrokeSelector){SGPenStrokeSelectorManagement::touchstart();}
}

void SGTouchInputManagement::drawongoing(){
    if(SGCentralManagement::activetooltype == SGToolTypeEnum::Move){
        if(SGTouchInputManagement::scrolltouch1.id != 0){
            SGTouchInputManagement::scrolltouch2 = SGTouchEvent(0, 0, false, SGTouchInputManagement::scrolltouch1.x, SGTouchInputManagement::scrolltouch1.y);
            SGTouchInputManagement::scrolltouch1 = SGTouchEvent(0, 0, false, SGTouchInputManagement::drawingtouch.x, SGTouchInputManagement::drawingtouch.y);
            SGViewportManagement::zoomongoing();
        }
        else{
            SGTouchInputManagement::scrolltouch1 = SGTouchEvent(0, 0, false, SGTouchInputManagement::drawingtouch.x, SGTouchInputManagement::drawingtouch.y);
            SGViewportManagement::moveongoing();
        }
    }
    else if(SGCentralManagement::activetooltype == SGToolTypeEnum::Pen){SGPenManagement::addtonewpenstroke();}
    else if(SGCentralManagement::activetooltype == SGToolTypeEnum::CompleteEraser || SGCentralManagement::activetooltype == SGToolTypeEnum::PartialEraser || SGCentralManagement::activetooltype == SGToolTypeEnum::HighlighterCompleteEraser || SGCentralManagement::activetooltype == SGToolTypeEnum::HighlighterPartialEraser){SGEraserManagement::moveeraser();}
    else if(SGCentralManagement::activetooltype == SGToolTypeEnum::Highlighter){SGHighlighterManagement::addtonewhighlighterstroke();}
    else if(SGCentralManagement::activetooltype == SGToolTypeEnum::PenStrokeSelector){SGPenStrokeSelectorManagement::touchongoing();}
}

void SGTouchInputManagement::drawend(){
    if(SGCentralManagement::activetooltype == SGToolTypeEnum::Pen){SGPenManagement::endnewpenstroke();}
    else if(SGCentralManagement::activetooltype == SGToolTypeEnum::CompleteEraser || SGCentralManagement::activetooltype == SGToolTypeEnum::PartialEraser || SGCentralManagement::activetooltype == SGToolTypeEnum::HighlighterCompleteEraser || SGCentralManagement::activetooltype == SGToolTypeEnum::HighlighterPartialEraser){SGEraserManagement::deleteeraser();}
    else if(SGCentralManagement::activetooltype == SGToolTypeEnum::Highlighter){SGHighlighterManagement::endnewhighlighterstroke();}
    else if(SGCentralManagement::activetooltype == SGToolTypeEnum::PenStrokeSelector){SGPenStrokeSelectorManagement::touchend();}
}

void SGTouchInputManagement::scroll1start(){
    if(SGCentralManagement::activetooltype == SGToolTypeEnum::Move){SGViewportManagement::movestart();}
}

void SGTouchInputManagement::scroll1ongoing(){
    if(SGCentralManagement::activetooltype == SGToolTypeEnum::Move){SGViewportManagement::moveongoing();}
}

void SGTouchInputManagement::scroll1end(){

}

void SGTouchInputManagement::scroll2start(){
    if(SGCentralManagement::activetooltype == SGToolTypeEnum::Move){SGViewportManagement::zoomstart();}
}

void SGTouchInputManagement::scroll2ongoing(){
    if(SGCentralManagement::activetooltype == SGToolTypeEnum::Move){SGViewportManagement::zoomongoing();}
}

void SGTouchInputManagement::scroll2end(){

}

void SGTouchInputManagement::selectstart(){

}

void SGTouchInputManagement::selectongoing(){

}

void SGTouchInputManagement::selectend(){

}

void SGTouchInputManagement::quickmovestart(){
    if(SGTouchInputManagement::selecttouch.x > SGTouchInputManagement::quickmovex * SGCentralManagement::sizeunit && SGTouchInputManagement::selecttouch.x < SGTouchInputManagement::quickmovex * SGCentralManagement::sizeunit + 1.5f * SGCentralManagement::sizeunit && SGTouchInputManagement::selecttouch.y > SGTouchInputManagement::quickmovey * SGCentralManagement::sizeunit && SGTouchInputManagement::selecttouch.y < SGTouchInputManagement::quickmovey * SGCentralManagement::sizeunit + 1.5f * SGCentralManagement::sizeunit){
        SGTouchInputManagement::quickmovemode = 1;
        (*SGTouchInputManagement::quickmovetimer).restart();
    }
    else if(SGNoteViewManagement::quickmoveenabled && SGTouchInputManagement::selecttouch.x > SGTouchInputManagement::quickmovex * SGCentralManagement::sizeunit && SGTouchInputManagement::selecttouch.x < SGTouchInputManagement::quickmovex * SGCentralManagement::sizeunit + 1.5f * SGCentralManagement::sizeunit && SGTouchInputManagement::selecttouch.y > SGTouchInputManagement::quickmovey * SGCentralManagement::sizeunit - 1.5f * SGCentralManagement::sizeunit && SGTouchInputManagement::selecttouch.y < SGTouchInputManagement::quickmovey * SGCentralManagement::sizeunit){
        SGTouchInputManagement::quickmovemode = 2;
        (*SGTouchInputManagement::quickmovetimer).restart();
        SGNoteQuickMoveManagement::n = 0;
        SGNoteQuickMoveManagement::startposy = SGCentralManagement::focusedpositiony;
        (*SGNoteQuickMoveManagement::quickmovetimer).start(16);
    }
    else if(SGNoteViewManagement::quickmoveenabled && SGTouchInputManagement::selecttouch.x > SGTouchInputManagement::quickmovex * SGCentralManagement::sizeunit && SGTouchInputManagement::selecttouch.x < SGTouchInputManagement::quickmovex * SGCentralManagement::sizeunit + 1.5f * SGCentralManagement::sizeunit && SGTouchInputManagement::selecttouch.y > SGTouchInputManagement::quickmovey * SGCentralManagement::sizeunit + 1.5f * SGCentralManagement::sizeunit && SGTouchInputManagement::selecttouch.y < SGTouchInputManagement::quickmovey * SGCentralManagement::sizeunit + 3.0f * SGCentralManagement::sizeunit){
        SGTouchInputManagement::quickmovemode = 3;
        (*SGTouchInputManagement::quickmovetimer).restart();
        SGNoteQuickMoveManagement::n = 0;
        SGNoteQuickMoveManagement::startposy = SGCentralManagement::focusedpositiony;
        (*SGNoteQuickMoveManagement::quickmovetimer).start(16);
    }
    else if(SGNoteViewManagement::quickmoveenabled && SGTouchInputManagement::selecttouch.x > SGTouchInputManagement::quickmovex * SGCentralManagement::sizeunit - 1.5f * SGCentralManagement::sizeunit && SGTouchInputManagement::selecttouch.x < SGTouchInputManagement::quickmovex * SGCentralManagement::sizeunit && SGTouchInputManagement::selecttouch.y > SGTouchInputManagement::quickmovey * SGCentralManagement::sizeunit && SGTouchInputManagement::selecttouch.y < SGTouchInputManagement::quickmovey * SGCentralManagement::sizeunit + 1.5f * SGCentralManagement::sizeunit){
        SGTouchInputManagement::quickmovemode = 4;
        (*SGTouchInputManagement::quickmovetimer).restart();
        SGNoteQuickMoveManagement::n = 0;
        SGNoteQuickMoveManagement::startposx = SGCentralManagement::focusedpositionx;
        (*SGNoteQuickMoveManagement::quickmovetimer).start(16);
    }
    else if(SGNoteViewManagement::quickmoveenabled && SGTouchInputManagement::selecttouch.x > SGTouchInputManagement::quickmovex * SGCentralManagement::sizeunit + 1.5f * SGCentralManagement::sizeunit && SGTouchInputManagement::selecttouch.x < SGTouchInputManagement::quickmovex * SGCentralManagement::sizeunit + 3.0f * SGCentralManagement::sizeunit && SGTouchInputManagement::selecttouch.y > SGTouchInputManagement::quickmovey * SGCentralManagement::sizeunit && SGTouchInputManagement::selecttouch.y < SGTouchInputManagement::quickmovey * SGCentralManagement::sizeunit + 1.5f * SGCentralManagement::sizeunit){
        SGTouchInputManagement::quickmovemode = 5;
        (*SGTouchInputManagement::quickmovetimer).restart();
        SGNoteQuickMoveManagement::n = 0;
        SGNoteQuickMoveManagement::startposx = SGCentralManagement::focusedpositionx;
        (*SGNoteQuickMoveManagement::quickmovetimer).start(16);
    }
    else if(SGNoteViewManagement::quickmoveenabled && SGTouchInputManagement::selecttouch.x > SGTouchInputManagement::quickmovex * SGCentralManagement::sizeunit - 0.75f * SGCentralManagement::sizeunit && SGTouchInputManagement::selecttouch.x < SGTouchInputManagement::quickmovex * SGCentralManagement::sizeunit + 0.75f * SGCentralManagement::sizeunit && SGTouchInputManagement::selecttouch.y > SGTouchInputManagement::quickmovey * SGCentralManagement::sizeunit + 3.0f * SGCentralManagement::sizeunit && SGTouchInputManagement::selecttouch.y < SGTouchInputManagement::quickmovey * SGCentralManagement::sizeunit + 4.5f * SGCentralManagement::sizeunit){
        SGTouchInputManagement::quickmovemode = 6;
        (*SGTouchInputManagement::quickmovetimer).restart();
        SGNoteQuickMoveManagement::n = 0;
        SGNoteQuickMoveManagement::startzoom = SGCentralManagement::focusedzoom;
        (*SGNoteQuickMoveManagement::quickmovetimer).start(16);
    }
    else if(SGNoteViewManagement::quickmoveenabled && SGTouchInputManagement::selecttouch.x > SGTouchInputManagement::quickmovex * SGCentralManagement::sizeunit + 0.75f * SGCentralManagement::sizeunit && SGTouchInputManagement::selecttouch.x < SGTouchInputManagement::quickmovex * SGCentralManagement::sizeunit + 2.25f * SGCentralManagement::sizeunit && SGTouchInputManagement::selecttouch.y > SGTouchInputManagement::quickmovey * SGCentralManagement::sizeunit + 3.0f * SGCentralManagement::sizeunit && SGTouchInputManagement::selecttouch.y < SGTouchInputManagement::quickmovey * SGCentralManagement::sizeunit + 4.5f * SGCentralManagement::sizeunit){
        SGTouchInputManagement::quickmovemode = 7;
        (*SGTouchInputManagement::quickmovetimer).restart();
        SGNoteQuickMoveManagement::n = 0;
        SGNoteQuickMoveManagement::startzoom = SGCentralManagement::focusedzoom;
        (*SGNoteQuickMoveManagement::quickmovetimer).start(16);
    }
}

void SGTouchInputManagement::quickmoveongoing(){
    if(SGTouchInputManagement::quickmovemode == 1){
        SGTouchInputManagement::quickmovex = SGTouchInputManagement::selecttouch.x / SGCentralManagement::sizeunit - 0.75f;
        SGTouchInputManagement::quickmovey = SGTouchInputManagement::selecttouch.y / SGCentralManagement::sizeunit - 0.75f;
        (*SGNoteViewManagement::quickmoverenderer).update();
    }
    else if(SGTouchInputManagement::quickmovemode == 2){
        SGTouchInputManagement::quickmovex = SGTouchInputManagement::selecttouch.x / SGCentralManagement::sizeunit - 0.75f;
        SGTouchInputManagement::quickmovey = SGTouchInputManagement::selecttouch.y / SGCentralManagement::sizeunit + 0.75f;
        (*SGNoteViewManagement::quickmoverenderer).update();
    }
    else if(SGTouchInputManagement::quickmovemode == 3){
        SGTouchInputManagement::quickmovex = SGTouchInputManagement::selecttouch.x / SGCentralManagement::sizeunit - 0.75f;
        SGTouchInputManagement::quickmovey = SGTouchInputManagement::selecttouch.y / SGCentralManagement::sizeunit - 2.25f;
        (*SGNoteViewManagement::quickmoverenderer).update();
    }
    else if(SGTouchInputManagement::quickmovemode == 4){
        SGTouchInputManagement::quickmovex = SGTouchInputManagement::selecttouch.x / SGCentralManagement::sizeunit + 0.75f;
        SGTouchInputManagement::quickmovey = SGTouchInputManagement::selecttouch.y / SGCentralManagement::sizeunit - 0.75f;
        (*SGNoteViewManagement::quickmoverenderer).update();
    }
    else if(SGTouchInputManagement::quickmovemode == 5){
        SGTouchInputManagement::quickmovex = SGTouchInputManagement::selecttouch.x / SGCentralManagement::sizeunit - 2.25f;
        SGTouchInputManagement::quickmovey = SGTouchInputManagement::selecttouch.y / SGCentralManagement::sizeunit - 0.75f;
        (*SGNoteViewManagement::quickmoverenderer).update();
    }
    else if(SGTouchInputManagement::quickmovemode == 6){
        SGTouchInputManagement::quickmovex = SGTouchInputManagement::selecttouch.x / SGCentralManagement::sizeunit;
        SGTouchInputManagement::quickmovey = SGTouchInputManagement::selecttouch.y / SGCentralManagement::sizeunit - 3.75f;
        (*SGNoteViewManagement::quickmoverenderer).update();
    }
    else if(SGTouchInputManagement::quickmovemode == 7){
        SGTouchInputManagement::quickmovex = SGTouchInputManagement::selecttouch.x / SGCentralManagement::sizeunit - 1.5f;
        SGTouchInputManagement::quickmovey = SGTouchInputManagement::selecttouch.y / SGCentralManagement::sizeunit - 3.75f;
        (*SGNoteViewManagement::quickmoverenderer).update();
    }
}

void SGTouchInputManagement::quickmoveend(){
    if(SGTouchInputManagement::quickmovemode == 1){
        SGTouchInputManagement::quickmovemode = 0;
        if((*SGTouchInputManagement::quickmovetimer).elapsed() < 200){
            if(SGNoteViewManagement::quickmoveenabled){SGNoteViewManagement::quickmoveenabled = false;}
            else{SGNoteViewManagement::quickmoveenabled = true;}
            (*SGNoteViewManagement::quickmoverenderer).update();
        }
    }
    else if(SGTouchInputManagement::quickmovemode != 0){
        SGTouchInputManagement::quickmovemode = 0;
        (*SGNoteQuickMoveManagement::quickmovetimer).stop();
    }
}
