#ifndef SGWIDGET___1111_2_H
#define SGWIDGET___1111_2_H

#include <QWidget>

class SGWidget000111102 : public QWidget
{
    Q_OBJECT
public:
    SGWidget000111102(QWidget* parent, float x, float y, float w, float h);
    float x;
    float y;
    float w;
    float h;
public slots:
    void ResizeObj();
};

#endif // SGWIDGET___1111_2_H
