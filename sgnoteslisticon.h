#ifndef SGNOTESLISTICON_H
#define SGNOTESLISTICON_H

#include <QWidget>
#include "sgwidgetbutton000110001.h"

class SGNotesListIcon : public SGWidgetButton000110001
{
    Q_OBJECT
public:
    SGNotesListIcon(QWidget *parent, float w, float h, QString& s);
    QString path;

public slots:
    void openfolder();
    void openfile();
};

#endif // SGNOTESLISTICON_H
