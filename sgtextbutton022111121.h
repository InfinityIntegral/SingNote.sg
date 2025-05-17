#ifndef SGTEXTBUTTON022111121_H
#define SGTEXTBUTTON022111121_H

#include <QWidget>
#include <QPushButton>

class SGTextButton022111121 : public QPushButton
{
    Q_OBJECT
public:
    SGTextButton022111121(QWidget *parent, QString s, float x, float y, float w, float h);
    float x;
    float y;
    float w;
    float h;

public slots:
    void ResizeObj();
};

#endif // SGTEXTBUTTON022111121_H
