#include "sglayoutchangeselector.h"
#include <QTimer>
#include "sgcentralmanagement.h"
#include "sgtooloptionsmanagement.h"

SGLayoutChangeSelector::SGLayoutChangeSelector(QWidget *parent){
    (*this).setParent(parent);
    (*this).show();
    (*this).ReceiveUpdateCall();
}

void SGLayoutChangeSelector::ReceiveUpdateCall(){
    (*this).move(QPoint(0.0f, 0.0f));
    QTimer::singleShot(0, this, &SGLayoutChangeSelector::ResizeObj);
}

void SGLayoutChangeSelector::ResizeObj(){
    float x = 0.0f;
    float y = 0.0f;
    float w = (*parentWidget()).size().width() / SGCentralManagement::sizeunit;
    (*SGToolOptionsManagement::changeselectortitletext).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    y += 1.5f;
    (*SGToolOptionsManagement::changeselectorpenstrokebutton).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    y += 1.0f;
    (*SGToolOptionsManagement::changeselectorboxbutton).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    y += 1.0f;
    (*SGToolOptionsManagement::changeselectorglobalbutton).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    y += 1.0f;
    (*SGToolOptionsManagement::changeselectorshapebutton).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    y += 1.0f;
    (*this).resize(QSize(w * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
}
