#ifndef SGINPUTFIELD312211232_H
#define SGINPUTFIELD312211232_H

#include <QWidget>
#include "sginputfield3.h"

class SGInputField312211232 : public SGInputField3
{
    Q_OBJECT
public:
    SGInputField312211232(QWidget *parent, float x, float y, float h);
    float x;
    float y;
    float h;

public slots:
    void ResizeObj();
};

#endif // SGINPUTFIELD312211232_H
