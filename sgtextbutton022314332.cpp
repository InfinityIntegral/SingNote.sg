#include "sgtextbutton022314332.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"

SGTextButton022314332::SGTextButton022314332(QWidget *parent, QString s, float x1, float x0, float y, float w1, float w0, float h){
    (*this).setParent(parent);
    (*this).x1 = x1;
    (*this).x0 = x0;
    (*this).y = y;
    (*this).w1 = w1;
    (*this).w0 = w0;
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

void SGTextButton022314332::ResizeObj(){
    (*this).move(QPoint(x1 * (*parentWidget()).size().width() + x0 * SGCentralManagement::sizeunit, (*parentWidget()).size().height() - y * SGCentralManagement::sizeunit));
    (*this).resize(QSize(w1 * (*parentWidget()).size().width() + w0 * SGCentralManagement::sizeunit, h * SGCentralManagement::sizeunit));
    SGGeneralLibrary::updatefontsize(this);
}
