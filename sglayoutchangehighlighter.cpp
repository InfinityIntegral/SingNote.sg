#include "sglayoutchangehighlighter.h"
#include <QTimer>
#include "sgcentralmanagement.h"
#include "sgtooloptionsmanagement.h"

SGLayoutChangeHighlighter::SGLayoutChangeHighlighter(QWidget *parent){
    (*this).setParent(parent);
    (*this).show();
    (*this).ReceiveUpdateCall();
}

void SGLayoutChangeHighlighter::ReceiveUpdateCall(){
    (*this).move(QPoint(0.0f, 0.0f));
    QTimer::singleShot(0, this, &SGLayoutChangeHighlighter::ResizeObj);
}

void SGLayoutChangeHighlighter::ResizeObj(){
    float x = 0.0f;
    float y = 0.0f;
    float w = (*parentWidget()).size().width() / SGCentralManagement::sizeunit;
    (*SGToolOptionsManagement::changehighlightertitletext).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    y += 1.5f;
    (*SGToolOptionsManagement::changehighlightercolourtext).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    x += 2.0f;
    if(w - x < 8.0f){
        x = 0.0f;
        y += 1.5f;
    }
    (*SGToolOptionsManagement::changehighlighterredinput).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    x += 2.0f;
    (*SGToolOptionsManagement::changehighlightergreeninput).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    x += 2.0f;
    (*SGToolOptionsManagement::changehighlighterblueinput).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    x += 2.0f;
    (*SGToolOptionsManagement::changehighlightertransparencyinput).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    x = 0.0f;
    y += 1.5f;
    (*SGToolOptionsManagement::changehighlighterwidthtext).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    x += 2.0f;
    if(w - x < 4.0f){
        x = 0.0f;
        y += 1.5f;
    }
    (*SGToolOptionsManagement::changehighlighterwidthinput).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    y += 1.5f;
    (*this).resize(QSize(w * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
}
