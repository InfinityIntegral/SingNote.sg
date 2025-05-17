#ifndef SGLAYOUTFAVOURITETOOLS_H
#define SGLAYOUTFAVOURITETOOLS_H

#include <QWidget>
#include "sgfavouritetoolbutton.h"

class SGLayoutFavouriteTools : public QWidget
{
    Q_OBJECT
public:
    SGLayoutFavouriteTools(QWidget* parent);
    ~SGLayoutFavouriteTools();
    QVector<QWidget*>* objlist;

public slots:
    void ReceiveUpdateCall();
    void ResizeObj();
};

#endif // SGLAYOUTFAVOURITETOOLS_H
