#ifndef SGDIRECTORYVIEWMANAGEMENT_H
#define SGDIRECTORYVIEWMANAGEMENT_H

#include <QObject>
#include "sgwidget000211103.h"
#include "sglayoutdirectorytoolbar.h"
#include "sgiconbutton022110032.h"

class SGDirectoryViewManagement : public QObject
{
    Q_OBJECT
public:
    static void initialisedirectorytoolbar();
    static SGWidget000211103* toolbarbackground;
    static SGLayoutDirectoryToolbar* toolbarlayout;
    static SGIconButton022110032* newfilebutton;
    static SGIconButton022110032* exitfolderbutton;
    static SGIconButton022110032* refreshnoteslistsbutton;

private:
    SGDirectoryViewManagement(){}
    ~SGDirectoryViewManagement(){}
};

#endif // SGDIRECTORYVIEWMANAGEMENT_H
