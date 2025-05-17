#include "sgwidget000111102.h"
#include "sgcentralmanagement.h"
#include "sggenerallibrary.h"

SGWidget000111102::SGWidget000111102(QWidget *parent, float x, float y, float w, float h){
    (*this).setParent(parent);
    (*this).x = x;
    (*this).y = y;
    (*this).w = w;
    (*this).h = h;
    (*this).show();
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
    (*this).setAutoFillBackground(true);
    (*this).ResizeObj();
}

void SGWidget000111102::ResizeObj(){
    (*this).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    (*this).resize(QSize(w * SGCentralManagement::sizeunit, h * SGCentralManagement::sizeunit));
}
