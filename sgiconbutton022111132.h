#ifndef SGICONBUTTON_22111132_H
#define SGICONBUTTON_22111132_H

#include <QWidget>
#include <QPushButton>

class SGIconButton022111132 : public QPushButton
{
    Q_OBJECT
public:
    SGIconButton022111132(QWidget* parent, QString s, float x, float y, float w, float h);
    float x;
    float y;
    float w;
    float h;
public slots:
    void ResizeObj();
};

#endif // SGICONBUTTON_22111132_H
