#ifndef SGLAYOUTNOTETOOLBAR_H
#define SGLAYOUTNOTETOOLBAR_H

#include <QWidget>
#include "sgiconbutton022110032.h"

class SGLayoutNoteToolbar : public QWidget
{
    Q_OBJECT
public:
    SGLayoutNoteToolbar(QWidget *parent);
    ~SGLayoutNoteToolbar();
    int cnt;
    QWidget** objlist;
public slots:
    void ReceiveUpdateCall();
    void ResizeObj();
};

#endif // SGLAYOUTNOTETOOLBAR_H
