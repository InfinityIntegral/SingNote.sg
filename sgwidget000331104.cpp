#include "sgwidget000331104.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"

SGWidget000331104::SGWidget000331104(QWidget *parent, float x, float y, float w1, float w0, float h1, float h0){
    (*this).setParent(parent);
    (*this).x = x;
    (*this).y = y;
    (*this).w1 = w1;
    (*this).w0 = w0;
    (*this).h1 = h1;
    (*this).h0 = h0;
    (*this).show();
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    (*this).setAutoFillBackground(true);
    (*this).ResizeObj();
}

void SGWidget000331104::ResizeObj(){
    (*this).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    (*this).resize(QSize(w1 * (*parentWidget()).size().width() + w0 * SGCentralManagement::sizeunit, h1 * (*parentWidget()).size().height() + h0 * SGCentralManagement::sizeunit));
}
