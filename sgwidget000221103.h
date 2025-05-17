#ifndef SGWIDGET000221103_H
#define SGWIDGET000221103_H

#include <QWidget>

class SGWidget000221103 : public QWidget
{
    Q_OBJECT
public:
    SGWidget000221103(QWidget *parent, float x, float y);
    float x;
    float y;

public slots:
    void ResizeObj();
};

#endif // SGWIDGET000221103_H
