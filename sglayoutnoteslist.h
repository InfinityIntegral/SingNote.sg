#ifndef SGLAYOUTNOTESLIST_H
#define SGLAYOUTNOTESLIST_H

#include <QWidget>
#include "sgnoteslisticon.h"

class SGLayoutNotesList : public QWidget
{
    Q_OBJECT
public:
    SGLayoutNotesList(QWidget *parent);
    ~SGLayoutNotesList();
    int n;
    SGNotesListIcon** buttonslist;

public slots:
    void ReceiveUpdateCall();
    void ResizeObj();
};

#endif // SGLAYOUTNOTESLIST_H
