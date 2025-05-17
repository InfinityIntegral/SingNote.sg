#include "sgviewportmanagement.h"
#include "sgcentralmanagement.h"
#include "sgtouchinputmanagement.h"
#include "sgnoteviewmanagement.h"

float SGViewportManagement::startfocusedposx = 0.0f;
float SGViewportManagement::startfocusedposy = 0.0f;
float SGViewportManagement::startfocusedzoom = 0.0f;
float SGViewportManagement::startscroll1x = 0.5f;
float SGViewportManagement::startscroll1y = 0.5f;
float SGViewportManagement::startscroll2x = 0.5f;
float SGViewportManagement::startscroll2y = 0.5f;

void SGViewportManagement::movestart(){
    if(SGTouchInputManagement::scrolltouch2.id != 0){return;}
    SGViewportManagement::startfocusedposx = SGCentralManagement::focusedpositionx;
    SGViewportManagement::startfocusedposy = SGCentralManagement::focusedpositiony;
    SGViewportManagement::startscroll1x = SGTouchInputManagement::scrolltouch1.x;
    SGViewportManagement::startscroll1y = SGTouchInputManagement::scrolltouch1.y;
    SGNoteViewManagement::updaterendering();
}

void SGViewportManagement::moveongoing(){
    if(SGTouchInputManagement::scrolltouch2.id != 0){return;}
    SGCentralManagement::focusedpositionx = SGViewportManagement::startfocusedposx - SGCentralManagement::focusedzoom / (*SGNoteViewManagement::renderarea).size().width() * (SGTouchInputManagement::scrolltouch1.x - SGViewportManagement::startscroll1x);
    SGCentralManagement::focusedpositiony = SGViewportManagement::startfocusedposy + SGCentralManagement::focusedzoom / (*SGNoteViewManagement::renderarea).size().width() * (SGTouchInputManagement::scrolltouch1.y - SGViewportManagement::startscroll1y);
    SGNoteViewManagement::updaterendering();
}

void SGViewportManagement::zoomstart(){
    SGViewportManagement::startfocusedzoom = SGCentralManagement::focusedzoom;
    SGViewportManagement::startscroll1x = SGTouchInputManagement::scrolltouch1.x;
    SGViewportManagement::startscroll1y = SGTouchInputManagement::scrolltouch1.y;
    SGViewportManagement::startscroll2x = SGTouchInputManagement::scrolltouch2.x;
    SGViewportManagement::startscroll2y = SGTouchInputManagement::scrolltouch2.y;
}

void SGViewportManagement::zoomongoing(){
    SGCentralManagement::focusedzoom = SGViewportManagement::startfocusedzoom * std::sqrtf((SGTouchInputManagement::scrolltouch1.x - SGTouchInputManagement::scrolltouch2.x) * (SGTouchInputManagement::scrolltouch1.x - SGTouchInputManagement::scrolltouch2.x) + (SGTouchInputManagement::scrolltouch1.y - SGTouchInputManagement::scrolltouch2.y) * (SGTouchInputManagement::scrolltouch1.y - SGTouchInputManagement::scrolltouch2.y)) / std::sqrtf((SGViewportManagement::startscroll1x - SGViewportManagement::startscroll2x) * (SGViewportManagement::startscroll1x - SGViewportManagement::startscroll2x) + (SGViewportManagement::startscroll1y - SGViewportManagement::startscroll2y) * (SGViewportManagement::startscroll1y - SGViewportManagement::startscroll2y));
    SGNoteViewManagement::updaterendering();
}
