#include "sginputfield312211232.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"

SGInputField312211232::SGInputField312211232(QWidget *parent, float x, float y, float h){
    (*this).setParent(parent);
    (*this).x = x;
    (*this).y = y;
    (*this).h = h;
    (*this).show();
    (*this).setFont(*SGGeneralLibrary::SingScriptSG);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldtextcolour, SGCentralManagement::colour2);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldselectedtextcolour, SGCentralManagement::colour1);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldselectedbackgroundcolour, SGCentralManagement::colour2);
    (*this).setFrame(QFrame::NoFrame);
    (*this).setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    (*this).ResizeObj();
}

void SGInputField312211232::ResizeObj(){
    (*this).move(QPoint(x * SGCentralManagement::sizeunit, 0.5f * (*parentWidget()).size().height() + y * SGCentralManagement::sizeunit));
    (*this).resize(QSize((*parentWidget()).size().width(), h * SGCentralManagement::sizeunit));
    SGGeneralLibrary::updatefontsize(this);
}
