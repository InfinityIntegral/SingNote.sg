#ifndef SGTEXTBUTTON022110032_H
#define SGTEXTBUTTON022110032_H

#include <QWidget>
#include <QPushButton>

class SGTextButton022110032 : public QPushButton
{
    Q_OBJECT
public:
    SGTextButton022110032(QWidget *parent, QString s, float w, float h);
    float w;
    float h;

public slots:
    void ResizeObj();
};

#endif // SGTEXTBUTTON022110032_H
