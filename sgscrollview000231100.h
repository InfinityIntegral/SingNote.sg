#ifndef SGSCROLLVIEW000231100_H
#define SGSCROLLVIEW000231100_H

#include <QWidget>
#include <QScrollArea>

class SGScrollView000231100 : public QScrollArea
{
    Q_OBJECT
public:
    SGScrollView000231100(QWidget *parent, float x, float y, float h1, float h0);
    float x;
    float y;
    float h1;
    float h0;

public slots:
    void ResizeObj();
};

#endif // SGSCROLLVIEW000231100_H
