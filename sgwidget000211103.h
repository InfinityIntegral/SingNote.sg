#ifndef SGWidget000211103_H
#define SGWidget000211103_H

#include <QWidget>

class SGWidget000211103 : public QWidget
{
    Q_OBJECT
public:
    SGWidget000211103(QWidget *parent, float x, float y, float h);
    float x;
    float y;
    float h;

public slots:
    void ResizeObj();
};

#endif // SGWidget000211103_H
