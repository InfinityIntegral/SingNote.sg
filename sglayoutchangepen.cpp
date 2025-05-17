#include "sglayoutchangepen.h"
#include <QTimer>
#include "sgcentralmanagement.h"
#include "sggenerallibrary.h"
#include "sgtooloptionsmanagement.h"

SGLayoutChangePen::SGLayoutChangePen(QWidget *parent){
    (*this).setParent(parent);
    (*this).show();
    (*this).ReceiveUpdateCall();
}

void SGLayoutChangePen::ReceiveUpdateCall(){
    (*this).move(QPoint(0.0f, 0.0f));
    QTimer::singleShot(0, this, &SGLayoutChangePen::ResizeObj);
}

void SGLayoutChangePen::ResizeObj(){
    float x = 0.0f;
    float y = 0.0f;
    float w = (*parentWidget()).size().width() / SGCentralManagement::sizeunit;
    (*SGToolOptionsManagement::changepentitletext).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    y += 1.5f;
    (*SGToolOptionsManagement::changepencolourtext).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    x += 2.0f;
    if(w - x < 6.0f){
        x = 0.0f;
        y += 1.5f;
    }
    (*SGToolOptionsManagement::changepenredinput).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    x += 2.0f;
    (*SGToolOptionsManagement::changepengreeninput).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    x += 2.0f;
    (*SGToolOptionsManagement::changepenblueinput).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    x = 0.0f;
    y += 1.5f;
    (*SGToolOptionsManagement::changepenwidthtext).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    x += 2.0f;
    if(w - x < 4.0f){
        x = 0.0f;
        y += 1.5f;
    }
    (*SGToolOptionsManagement::changepenwidthinput).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    y += 1.5f;
    (*this).resize(QSize(w * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
}
