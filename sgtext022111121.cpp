#include "sgtext022111121.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"

SGText022111121::SGText022111121(QWidget *parent, QString s, float x, float y, float w, float h){
    (*this).setParent(parent);
    (*this).x = x;
    (*this).y = y;
    (*this).w = w;
    (*this).h = h;
    (*this).show();
    (*this).setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    (*this).setFont(*SGGeneralLibrary::SingScriptSG);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldtextcolour, SGCentralManagement::colour1);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour0);
    (*this).setAutoFillBackground(true);
    (*this).setText(s);
    (*this).ResizeObj();
}

void SGText022111121::ResizeObj(){
    (*this).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    (*this).resize(QSize(w * SGCentralManagement::sizeunit, h * SGCentralManagement::sizeunit));
    SGGeneralLibrary::updatefontsize(this);
}
