#ifndef SGNOTESLISTMANAGEMENT_H
#define SGNOTESLISTMANAGEMENT_H

#include <QObject>
#include "sgtext012211121.h"
#include "sgscrollview000231100.h"
#include "sglayoutnoteslist.h"

class SGNotesListManagement : public QObject
{
    Q_OBJECT
public:
    static void noteslistinitialise();
    static void refreshnoteslist();
    static SGText012211121* folderaddressdisplay;
    static SGScrollView000231100* noteslistscrollview;
    static SGLayoutNotesList* noteslistslayout;
    static void exitfolder();

private:
    SGNotesListManagement(){}
    ~SGNotesListManagement(){}
};

#endif // SGNOTESLISTMANAGEMENT_H
