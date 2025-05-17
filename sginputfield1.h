#ifndef SGINPUTFIELD1_H
#define SGINPUTFIELD1_H

#include <QWidget>
#include <QLineEdit>

class SGInputField1 : public QLineEdit
{
    Q_OBJECT
public:
    void setinvalid();

public slots:
    void unsetinvalid();
};

#endif // SGINPUTFIELD1_H
