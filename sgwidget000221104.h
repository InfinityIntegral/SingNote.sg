#ifndef SGWIDGET000221104_H
#define SGWIDGET000221104_H

#include <QWidget>

class SGWidget000221104 : public QWidget
{
    Q_OBJECT
public:
    SGWidget000221104(QWidget *parent, float x, float y);
    float x;
    float y;

public slots:
    void ResizeObj();
};

#endif // SGWIDGET000221104_H
