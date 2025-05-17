#ifndef SGWIDGET000331104_H
#define SGWIDGET000331104_H

#include <QWidget>

class SGWidget000331104 : public QWidget
{
    Q_OBJECT
public:
    SGWidget000331104(QWidget *parent, float x, float y, float w1, float w0, float h1, float h0);
    float x;
    float y;
    float w1;
    float w0;
    float h1;
    float h0;

public slots:
    void ResizeObj();
};

#endif // SGWIDGET000331104_H
