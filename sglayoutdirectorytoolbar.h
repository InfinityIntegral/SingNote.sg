#ifndef SGLAYOUTDIRECTORYTOOLBAR_H
#define SGLAYOUTDIRECTORYTOOLBAR_H

#include <QWidget>
#include "sgiconbutton022110032.h"

class SGLayoutDirectoryToolbar : public QWidget
{
    Q_OBJECT
public:
    SGLayoutDirectoryToolbar(QWidget *parent);
    ~SGLayoutDirectoryToolbar();
    QWidget** objlist;
    int cnt;

public slots:
    void ReceiveUpdateCall();
    void ResizeObj();
};

#endif // SGLAYOUTDIRECTORYTOOLBAR_H
