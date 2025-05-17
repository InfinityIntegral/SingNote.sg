#ifndef SGINPUTFIELD2_H
#define SGINPUTFIELD2_H

#include <QWidget>
#include <QLineEdit>

class SGInputField2 : public QLineEdit
{
    Q_OBJECT
public:
    void setinvalid();

public slots:
    void unsetinvalid();
};

#endif // SGINPUTFIELD2_H
