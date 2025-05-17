#include "sgtext012110021.h"
#include "sgcentralmanagement.h"
#include "sggenerallibrary.h"

SGText012110021::SGText012110021(QWidget *parent, QString s, float w, float h){
    (*this).setParent(parent);
    (*this).w = w;
    (*this).h = h;
    (*this).show();
    (*this).setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    (*this).setFont(*SGGeneralLibrary::SingScriptSG);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldtextcolour, SGCentralManagement::colour1);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour0);
    (*this).setAutoFillBackground(true);
    (*this).setText(s);
    (*this).ResizeObj();
}

void SGText012110021::ResizeObj(){
    (*this).resize(QSize(w * SGCentralManagement::sizeunit, h * SGCentralManagement::sizeunit));
    SGGeneralLibrary::updatefontsize(this);
}
