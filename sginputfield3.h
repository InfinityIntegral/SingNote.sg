#ifndef SGINPUTFIELD3_H
#define SGINPUTFIELD3_H

#include <QWidget>
#include <QLineEdit>

class SGInputField3 : public QLineEdit
{
    Q_OBJECT
public:
    void setinvalid();

public slots:
    void unsetinvalid();
};

#endif // SGINPUTFIELD3_H
