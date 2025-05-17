#include "sgtext012211223.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"

SGText012211223::SGText012211223(QWidget *parent, QString s, float x, float y, float h){
    (*this).setParent(parent);
    (*this).x = x;
    (*this).y = y;
    (*this).h = h;
    (*this).show();
    (*this).setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    (*this).setFont(*SGGeneralLibrary::SingScriptSG);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldtextcolour, SGCentralManagement::colour1);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour2);
    (*this).setAutoFillBackground(true);
    (*this).setText(s);
    (*this).ResizeObj();
}

void SGText012211223::ResizeObj(){
    (*this).move(QPoint(x * SGCentralManagement::sizeunit, 0.5f * (*parentWidget()).size().height() + y * SGCentralManagement::sizeunit));
    (*this).resize(QSize((*parentWidget()).size().width(), h * SGCentralManagement::sizeunit));
    SGGeneralLibrary::updatefontsize(this);
}
