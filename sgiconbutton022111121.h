#ifndef SGICONBUTTON022111121_H
#define SGICONBUTTON022111121_H

#include <QWidget>
#include <QPushButton>

class SGIconButton022111121 : public QPushButton
{
    Q_OBJECT
public:
    SGIconButton022111121(QWidget *parent, QString s, float x, float y, float w, float h);
    float x;
    float y;
    float w;
    float h;
public slots:
    void ResizeObj();
};

#endif // SGICONBUTTON022111121_H
