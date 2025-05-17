#ifndef SGICONBUTTON022110032_H
#define SGICONBUTTON022110032_H

#include <QWidget>
#include <QPushButton>

class SGIconButton022110032 : public QPushButton
{
    Q_OBJECT
public:
    SGIconButton022110032(QWidget *parent, QString s, float w, float h);
    float w;
    float h;

public slots:
    void ResizeObj();
};

#endif // SGICONBUTTON022110032_H
