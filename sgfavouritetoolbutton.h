#ifndef SGFAVOURITETOOLBUTTON_H
#define SGFAVOURITETOOLBUTTON_H

#include "sgwidgetbutton000110001.h"
#include "sgwidget000111102.h"
#include "sgwidgetbutton000110001.h"
#include "sgtext012211121.h"
#include "sgiconbutton022111132.h"
#include "sgwidget000110001.h"

class SGFavouriteToolButton : public SGWidget000110001
{
    Q_OBJECT
public:
    SGFavouriteToolButton(QWidget* parent, int type, uint col, float width);
    SGWidget000111102* buttonbackground;
    SGText012211121* buttontext;
    SGIconButton022111132* buttonicon;
    int tooltype;
    uint toolcolour;
    float toolwidth;
    void refreshicon();
    int index;
    QMetaObject::Connection connection;
public slots:
    void setfavourite();
    void ResizeObj();
};

#endif // SGFAVOURITETOOLBUTTON_H
