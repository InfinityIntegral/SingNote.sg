#include "sgnoteviewtouchprocessor.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"
#include "sgtouchinputmanagement.h"

SGNoteViewTouchProcessor::SGNoteViewTouchProcessor(QWidget *parent){
    (*this).setParent(parent);
    (*this).setAttribute(Qt::WA_AcceptTouchEvents);
    (*this).show();
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour0);
    (*this).setAutoFillBackground(true);
    (*this).ResizeObj();
}

bool SGNoteViewTouchProcessor::event(QEvent *event){
    if((*event).type() == QEvent::TouchBegin || (*event).type() == QEvent::TouchUpdate || (*event).type() == QEvent::TouchEnd){
        QTouchEvent* te = (QTouchEvent*)(event);
        SGTouchInputManagement::processtouchfromqt(te);
        return true;
    }
    else if((*event).type() == QEvent::MouseButtonPress || (*event).type() == QEvent::MouseButtonRelease || (*event).type() == QEvent::MouseMove){return false;}
    return QWidget::event(event);
}

void SGNoteViewTouchProcessor::ResizeObj(){
    (*this).move(QPoint(0.0f, 0.0f));
    (*this).resize((*parentWidget()).size());
}
