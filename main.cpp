#include <QApplication>
#include "sgcentralmanagement.h"

int main(int argc, char** argv){
    QApplication app(argc, argv);
    SGCentralManagement::initialise();
    return app.exec();
}
