#include "sgwidget000211103.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"

SGWidget000211103::SGWidget000211103(QWidget *parent, float x, float y, float h){
    (*this).setParent(parent);
    (*this).x = x;
    (*this).y = y;
    (*this).h = h;
    (*this).show();
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour2);
    (*this).setAutoFillBackground(true);
    (*this).ResizeObj();
}

void SGWidget000211103::ResizeObj(){
    (*this).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    (*this).resize(QSize((*parentWidget()).size().width(), h * SGCentralManagement::sizeunit));
}
