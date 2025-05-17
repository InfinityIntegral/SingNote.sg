#ifndef SGNOTEVIEWTOUCHPROCESSOR_H
#define SGNOTEVIEWTOUCHPROCESSOR_H

#include <QWidget>
#include <QEvent>
#include <QTouchEvent>

class SGNoteViewTouchProcessor : public QWidget
{
    Q_OBJECT
public:
    SGNoteViewTouchProcessor(QWidget *parent);
    bool event(QEvent *event) override;

public slots:
    void ResizeObj();
};

#endif // SGNOTEVIEWTOUCHPROCESSOR_H
