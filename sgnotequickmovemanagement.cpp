#include "sgnotequickmovemanagement.h"
#include "sgtouchinputmanagement.h"
#include "sgcentralmanagement.h"
#include "sgnoteviewmanagement.h"

QTimer* SGNoteQuickMoveManagement::quickmovetimer = nullptr;
float SGNoteQuickMoveManagement::startposx = 0.0f;
float SGNoteQuickMoveManagement::startposy = 0.0f;
float SGNoteQuickMoveManagement::startzoom = 0.0f;
int SGNoteQuickMoveManagement::n = 0;

void SGNoteQuickMoveManagement::applyquickmove(){
    SGNoteQuickMoveManagement::n++;
    if(SGTouchInputManagement::quickmovemode == 2){
        SGCentralManagement::focusedpositiony = SGNoteQuickMoveManagement::startposy + 0.5f * (float)SGNoteQuickMoveManagement::n * SGCentralManagement::focusedzoom / 23.1f;
        SGNoteViewManagement::updaterendering();
    }
    else if(SGTouchInputManagement::quickmovemode == 3){
        SGCentralManagement::focusedpositiony = SGNoteQuickMoveManagement::startposy - 0.5f * (float)SGNoteQuickMoveManagement::n * SGCentralManagement::focusedzoom / 23.1f;
        SGNoteViewManagement::updaterendering();
    }
    else if(SGTouchInputManagement::quickmovemode == 4){
        SGCentralManagement::focusedpositionx = SGNoteQuickMoveManagement::startposx - 0.5f * (float)SGNoteQuickMoveManagement::n * SGCentralManagement::focusedzoom / 23.1f;
        SGNoteViewManagement::updaterendering();
    }
    else if(SGTouchInputManagement::quickmovemode == 5){
        SGCentralManagement::focusedpositionx = SGNoteQuickMoveManagement::startposx + 0.5f * (float)SGNoteQuickMoveManagement::n * SGCentralManagement::focusedzoom / 23.1f;
        SGNoteViewManagement::updaterendering();
    }
    else if(SGTouchInputManagement::quickmovemode == 6){
        SGCentralManagement::focusedzoom = SGNoteQuickMoveManagement::startzoom / std::powf(2.0f, (float)SGNoteQuickMoveManagement::n / 30.0f);
        SGNoteViewManagement::updaterendering();
    }
    else if(SGTouchInputManagement::quickmovemode == 7){
        SGCentralManagement::focusedzoom = SGNoteQuickMoveManagement::startzoom * std::powf(2.0f, (float)SGNoteQuickMoveManagement::n / 30.0f);
        SGNoteViewManagement::updaterendering();
    }
}
