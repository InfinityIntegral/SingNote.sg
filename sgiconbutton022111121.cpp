#include "sgiconbutton022111121.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"

SGIconButton022111121::SGIconButton022111121(QWidget *parent, QString s, float x, float y, float w, float h){
    (*this).setParent(parent);
    (*this).x = x;
    (*this).y = y;
    (*this).w = w;
    (*this).h = h;
    (*this).show();
    (*this).setFont(*SGCentralManagement::SingNoteIcons);
    (*this).setFlat(true);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldborder, SGGeneralLibrary::stylesheetnoborder);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldtextcolour, SGCentralManagement::colour1);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour0);
    (*this).setAutoFillBackground(true);
    (*this).setText(s);
    (*this).ResizeObj();
}

void SGIconButton022111121::ResizeObj(){
    (*this).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    (*this).resize(QSize(w * SGCentralManagement::sizeunit, h * SGCentralManagement::sizeunit));
    SGGeneralLibrary::updatefontsize(this);
}
