#ifndef SGLAYOUTCHANGEERASER_H
#define SGLAYOUTCHANGEERASER_H

#include <QWidget>

class SGLayoutChangeEraser : public QWidget
{
    Q_OBJECT
public:
    SGLayoutChangeEraser(QWidget *parent);

public slots:
    void ReceiveUpdateCall();
    void ResizeObj();
};

#endif // SGLAYOUTCHANGEERASER_H
