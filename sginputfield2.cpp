#include "sginputfield2.h"
#include "sgcentralmanagement.h"
#include "sggenerallibrary.h"
#include <QTimer>

void SGInputField2::setinvalid(){
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldselectedbackgroundcolour, SGCentralManagement::colour2);
    QTimer::singleShot(1000, this, &SGInputField2::unsetinvalid);
}

void SGInputField2::unsetinvalid(){
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldselectedbackgroundcolour, SGCentralManagement::colour2);
}
