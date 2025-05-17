#ifndef SGICON022111132_H
#define SGICON022111132_H

#include <QWidget>
#include <QLabel>

class SGIcon022111132 : public QLabel
{
    Q_OBJECT
public:
    SGIcon022111132(QWidget* parent, QString s, float x, float y, float w, float h);
    float x;
    float y;
    float w;
    float h;

public slots:
    void ResizeObj();
};

#endif // SGICON022111132_H
