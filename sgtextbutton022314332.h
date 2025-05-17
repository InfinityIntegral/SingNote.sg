#ifndef SGTEXTBUTTON022314332_H
#define SGTEXTBUTTON022314332_H

#include <QWidget>
#include <QPushButton>

class SGTextButton022314332 : public QPushButton
{
    Q_OBJECT
public:
    SGTextButton022314332(QWidget *parent, QString s, float x1, float x0, float y, float w1, float w0, float h);
    float x1;
    float x0;
    float y;
    float w1;
    float w0;
    float h;

public slots:
    void ResizeObj();
};

#endif // SGTEXTBUTTON022314332_H
