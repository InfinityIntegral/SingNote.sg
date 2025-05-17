#ifndef SGINPUTFIELD222110032_H
#define SGINPUTFIELD222110032_H

#include <QWidget>
#include "sginputfield2.h"

class SGInputField222110032 : public SGInputField2
{
    Q_OBJECT
public:
    SGInputField222110032(QWidget *parent, float w, float h);
    float w;
    float h;

public slots:
    void ResizeObj();
};

#endif // SGINPUTFIELD222110032_H
