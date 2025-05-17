#ifndef SGLAYOUTCHANGESELECTOR_H
#define SGLAYOUTCHANGESELECTOR_H

#include <QWidget>

class SGLayoutChangeSelector : public QWidget
{
    Q_OBJECT
public:
    SGLayoutChangeSelector(QWidget* parent);
public slots:
    void ReceiveUpdateCall();
    void ResizeObj();
};

#endif // SGLAYOUTCHANGESELECTOR_H
