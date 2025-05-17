#include "sgwidget000133103.h"
#include "sgcentralmanagement.h"
#include "sggenerallibrary.h"

SGWidget000133103::SGWidget000133103(QWidget *parent, float x, float y, float w, float h1, float h0){
    (*this).setParent(parent);
    (*this).x = x;
    (*this).y = y;
    (*this).w = w;
    (*this).h1 = h1;
    (*this).h0 = h0;
    (*this).show();
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour2);
    (*this).setAutoFillBackground(true);
    (*this).ResizeObj();
}

void SGWidget000133103::ResizeObj(){
    (*this).move(QPoint((*parentWidget()).size().width() - x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    (*this).resize(QSize(w * SGCentralManagement::sizeunit, h1 * (*parentWidget()).size().height() + h0 * SGCentralManagement::sizeunit));
}
