#include "sgwidget000221104.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"

SGWidget000221104::SGWidget000221104(QWidget *parent, float x, float y){
    (*this).setParent(parent);
    (*this).x = x;
    (*this).y = y;
    (*this).show();
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    (*this).setAutoFillBackground(true);
    (*this).ResizeObj();
}

void SGWidget000221104::ResizeObj(){
    (*this).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    (*this).resize((*parentWidget()).size());
}
