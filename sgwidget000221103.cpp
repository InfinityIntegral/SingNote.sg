#include "sgwidget000221103.h"
#include "sgcentralmanagement.h"
#include "sggenerallibrary.h"

SGWidget000221103::SGWidget000221103(QWidget *parent, float x, float y){
    (*this).setParent(parent);
    (*this).x = x;
    (*this).y = y;
    (*this).show();
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour2);
    (*this).setAutoFillBackground(true);
    (*this).ResizeObj();
}

void SGWidget000221103::ResizeObj(){
    (*this).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    (*this).resize((*parentWidget()).size());
}
