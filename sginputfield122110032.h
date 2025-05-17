#ifndef SGINPUTFIELD122110032_H
#define SGINPUTFIELD122110032_H

#include <QWidget>
#include "sginputfield1.h"

class SGInputField122110032 : public SGInputField1
{
    Q_OBJECT
public:
    SGInputField122110032(QWidget *parent, float w, float h);
    float w;
    float h;

public slots:
    void ResizeObj();
};

#endif // SGINPUTFIELD122110032_H
