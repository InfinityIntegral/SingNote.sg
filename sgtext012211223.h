#ifndef SGTEXT012211223_H
#define SGTEXT012211223_H

#include <QWidget>
#include <QLabel>

class SGText012211223 : public QLabel
{
    Q_OBJECT
public:
    SGText012211223(QWidget *parent, QString s, float x, float y, float h);
    float x;
    float y;
    float h;

public slots:
    void ResizeObj();
};

#endif // SGTEXT012211223_H
