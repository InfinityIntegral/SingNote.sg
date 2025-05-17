#ifndef SGTEXTBUTTON022211232_H
#define SGTEXTBUTTON022211232_H

#include <QWidget>
#include <QPushButton>

class SGTextButton022211232 : public QPushButton
{
    Q_OBJECT
public:
    SGTextButton022211232(QWidget *parent, QString s, float x, float y, float h);
    float x;
    float y;
    float h;

public slots:
    void ResizeObj();
};

#endif // SGTEXTBUTTON022211232_H
