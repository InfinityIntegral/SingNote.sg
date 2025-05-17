#ifndef SGLAYOUTCHANGEHIGHLIGHTER_H
#define SGLAYOUTCHANGEHIGHLIGHTER_H

#include <QWidget>

class SGLayoutChangeHighlighter : public QWidget
{
    Q_OBJECT
public:
    SGLayoutChangeHighlighter(QWidget* parent);

public slots:
    void ReceiveUpdateCall();
    void ResizeObj();
};

#endif // SGLAYOUTCHANGEHIGHLIGHTER_H
