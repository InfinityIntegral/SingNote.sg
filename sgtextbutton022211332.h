#ifndef SGTEXTBUTTON022211332_H
#define SGTEXTBUTTON022211332_H

#include <QWidget>
#include <QPushButton>

class SGTextButton022211332 : public QPushButton
{
    Q_OBJECT
public:
    SGTextButton022211332(QWidget *parent, QString s, float x, float y, float h);
    float x;
    float y;
    float h;

public slots:
    void ResizeObj();
};

#endif // SGTEXTBUTTON022211332_H
