#ifndef SGTEXT022111121_H
#define SGTEXT022111121_H

#include <QWidget>
#include <QLabel>

class SGText022111121 : public QLabel
{
    Q_OBJECT
public:
    SGText022111121(QWidget *parent, QString s, float x, float y, float w, float h);
    float x;
    float y;
    float w;
    float h;

public slots:
    void ResizeObj();
};

#endif // SGTEXT022111121_H
