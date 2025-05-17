#include "sgtextbutton022211332.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"

SGTextButton022211332::SGTextButton022211332(QWidget *parent, QString s, float x, float y, float h){
    (*this).setParent(parent);
    (*this).x = x;
    (*this).y = y;
    (*this).h = h;
    (*this).show();
    (*this).setFont(*SGGeneralLibrary::SingScriptSG);
    (*this).setFlat(true);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldborder, SGGeneralLibrary::stylesheetnoborder);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldtextcolour, SGCentralManagement::colour2);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
    (*this).setAutoFillBackground(true);
    (*this).setText(s);
    (*this).ResizeObj();
}

void SGTextButton022211332::ResizeObj(){
    (*this).move(QPoint(x * SGCentralManagement::sizeunit, (*parentWidget()).size().height() - y * SGCentralManagement::sizeunit));
    (*this).resize(QSize((*parentWidget()).size().width(), h * SGCentralManagement::sizeunit));
    SGGeneralLibrary::updatefontsize(this);
}
