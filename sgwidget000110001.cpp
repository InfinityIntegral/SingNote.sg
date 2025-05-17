#include "sgwidget000110001.h"
#include "sgcentralmanagement.h"
#include "sggenerallibrary.h"

SGWidget000110001::SGWidget000110001(QWidget *parent, float w, float h){
    (*this).setParent(parent);
    (*this).w = w;
    (*this).h = h;
    (*this).show();
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour0);
    (*this).setAutoFillBackground(true);
    (*this).ResizeObj();
}

void SGWidget000110001::ResizeObj(){
    (*this).resize(QSize(w * SGCentralManagement::sizeunit, h * SGCentralManagement::sizeunit));
}
