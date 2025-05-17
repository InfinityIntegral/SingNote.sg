#ifndef SGTEXT012211121_H
#define SGTEXT012211121_H

#include <QWidget>
#include <QLabel>

class SGText012211121 : public QLabel
{
    Q_OBJECT
public:
    SGText012211121(QWidget *parent, QString s, float x, float y, float h);
    float x;
    float y;
    float h;

public slots:
    void ResizeObj();
};

#endif // SGTEXT012211121_H
