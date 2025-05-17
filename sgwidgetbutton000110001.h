#ifndef SGWIDGETBUTTON000110001_H
#define SGWIDGETBUTTON000110001_H

#include <QWidget>
#include <QPushButton>

class SGWidgetButton000110001 : public QPushButton
{
    Q_OBJECT
public:
    SGWidgetButton000110001(QWidget *parent, float w, float h);
    float w;
    float h;

public slots:
    void ResizeObj();
};

#endif // SGWIDGETBUTTON000110001_H
