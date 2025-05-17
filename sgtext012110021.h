#ifndef SGTEXT012110021_H
#define SGTEXT012110021_H

#include <QWidget>
#include <QLabel>

class SGText012110021 : public QLabel
{
    Q_OBJECT
public:
    SGText012110021(QWidget *parent, QString s, float w, float h);
    float w;
    float h;

public slots:
    void ResizeObj();
};

#endif // SGTEXT012110021_H
