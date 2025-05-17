#ifndef SGLAYOUTCHANGEPEN_H
#define SGLAYOUTCHANGEPEN_H

#include <QWidget>

class SGLayoutChangePen : public QWidget
{
    Q_OBJECT
public:
    SGLayoutChangePen(QWidget *parent);

public slots:
    void ReceiveUpdateCall();
    void ResizeObj();
};

#endif // SGLAYOUTCHANGEPEN_H
