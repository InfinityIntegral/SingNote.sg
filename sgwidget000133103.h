#ifndef SGWIDGET___1331_3_H
#define SGWIDGET___1331_3_H

#include <QWidget>

class SGWidget000133103 : public QWidget
{
    Q_OBJECT
public:
    SGWidget000133103(QWidget* parent, float x, float y, float w, float h1, float h0);
    float x;
    float y;
    float w;
    float h1;
    float h0;
public slots:
    void ResizeObj();
};

#endif // SGWIDGET___1331_3_H
