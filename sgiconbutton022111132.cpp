#include "sgiconbutton022111132.h"
#include "sgcentralmanagement.h"
#include "sggenerallibrary.h"

SGIconButton022111132::SGIconButton022111132(QWidget *parent, QString s, float x, float y, float w, float h){
    (*this).setParent(parent);
    (*this).x = x;
    (*this).y = y;
    (*this).w = w;
    (*this).h = h;
    (*this).show();
    (*this).setFont(*SGCentralManagement::SingNoteIcons);
    (*this).setFlat(true);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldborder, SGGeneralLibrary::stylesheetnoborder);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldtextcolour, SGCentralManagement::colour2);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
    (*this).setAutoFillBackground(true);
    (*this).setText(s);
    (*this).ResizeObj();
}

void SGIconButton022111132::ResizeObj(){
    (*this).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    (*this).resize(QSize(w * SGCentralManagement::sizeunit, h * SGCentralManagement::sizeunit));
    SGGeneralLibrary::updatefontsize(this);
}
