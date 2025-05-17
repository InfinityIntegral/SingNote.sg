#ifndef SGWIDGET___11___1_H
#define SGWIDGET___11___1_H

#include <QWidget>

class SGWidget000110001 : public QWidget
{
    Q_OBJECT
public:
    SGWidget000110001(QWidget* parent, float w, float h);
    float w;
    float h;

public slots:
    void ResizeObj();
};

#endif // SGWIDGET___11___1_H
