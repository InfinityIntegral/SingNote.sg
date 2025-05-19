#include <QApplication>
#include "sgcentralmanagement.h"

int main(int argc, char** argv){
    QCoreApplication::setApplicationName("SingNote.sg");
    QCoreApplication::setApplicationVersion("1 + i");
    QCoreApplication::setOrganizationName("05524F.sg");
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/assets/05524Flogo.png"));
    SGCentralManagement::initialise();
    return app.exec();
}
