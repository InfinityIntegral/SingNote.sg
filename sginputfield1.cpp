#include "sginputfield1.h"
#include "sgcentralmanagement.h"
#include "sggenerallibrary.h"
#include <QTimer>

void SGInputField1::setinvalid(){
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour3);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldselectedbackgroundcolour, SGCentralManagement::colour2);
    QTimer::singleShot(1000, this, &SGInputField1::unsetinvalid);
}

void SGInputField1::unsetinvalid(){
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldbackgroundcolour, SGCentralManagement::colour1);
    SGGeneralLibrary::SetUIStyle(this, SGGeneralLibrary::stylesheetfieldselectedbackgroundcolour, SGCentralManagement::colour2);
}
