#include "sglayoutchangeeraser.h"
#include <QTimer>
#include "sgcentralmanagement.h"
#include "sgtooloptionsmanagement.h"

SGLayoutChangeEraser::SGLayoutChangeEraser(QWidget *parent){
    (*this).setParent(parent);
    (*this).show();
    (*this).ReceiveUpdateCall();
}

void SGLayoutChangeEraser::ReceiveUpdateCall(){
    (*this).move(QPoint(0.0f, 0.0f));
    QTimer::singleShot(0, this, &SGLayoutChangeEraser::ResizeObj);
}

void SGLayoutChangeEraser::ResizeObj(){
    float x = 0.0f;
    float y = 0.0f;
    float w = (*parentWidget()).size().width() / SGCentralManagement::sizeunit;
    (*SGToolOptionsManagement::changeerasertitletext).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    y += 1.5f;
    (*SGToolOptionsManagement::changeeraserwidthtext).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    x += 2.0f;
    if(w - x < 4.0f){
        x = 0.0f;
        y += 1.5f;
    }
    (*SGToolOptionsManagement::changeeraserwidthinput).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    x = 0.0f;
    y += 1.5f;
    (*SGToolOptionsManagement::changeerasercompletebutton).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    x += 5.5f;
    if(w - x < 5.0f){
        x = 0.0f;
        y += 1.0f;
    }
    (*SGToolOptionsManagement::changeeraserpartialbutton).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    x = 0.0f;
    y += 1.5f;
    (*SGToolOptionsManagement::changeerasereverythingbutton).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    x += 7.0f;
    if(w - x < 6.5f){
        x = 0.0f;
        y += 1.0f;
    }
    (*SGToolOptionsManagement::changeeraserhighlighterbutton).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    y += 1.5f;
    (*this).resize(QSize(w * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
}
