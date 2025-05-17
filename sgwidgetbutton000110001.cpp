#include "sgwidgetbutton000110001.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"

SGWidgetButton000110001::SGWidgetButton000110001(QWidget *parent, float w, float h){
    (*this).setParent(parent);
    (*this).w = w;
    (*this).h = h;
    (*this).show();
    (*this).setFlat(true);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldborder, SGGeneralLibrary::stylesheetnoborder);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour0);
    (*this).setAutoFillBackground(true);
    (*this).ResizeObj();
}

void SGWidgetButton000110001::ResizeObj(){
    (*this).resize(QSize(w * SGCentralManagement::sizeunit, h * SGCentralManagement::sizeunit));
}
