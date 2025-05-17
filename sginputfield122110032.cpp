#include "sginputfield122110032.h"
#include "sgcentralmanagement.h"
#include "sggenerallibrary.h"

SGInputField122110032::SGInputField122110032(QWidget *parent, float w, float h){
    (*this).setParent(parent);
    (*this).w = w;
    (*this).h = h;
    (*this).show();
    (*this).setFont(*SGGeneralLibrary::SingScriptSG);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldtextcolour, SGCentralManagement::colour2);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldselectedtextcolour, SGCentralManagement::colour1);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldselectedbackgroundcolour, SGCentralManagement::colour2);
    (*this).setFrame(QFrame::NoFrame);
    (*this).setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    (*this).ResizeObj();
}

void SGInputField122110032::ResizeObj(){
    (*this).resize(QSize(w * SGCentralManagement::sizeunit, h * SGCentralManagement::sizeunit));
    SGGeneralLibrary::updatefontsize(this);
}
