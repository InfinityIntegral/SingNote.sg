#ifndef SGTOOLTYPEENUM_H
#define SGTOOLTYPEENUM_H

#include <QObject>

class SGToolTypeEnum : public QObject
{
    Q_OBJECT
public:
    static int Move;
    static int Pen;
    static int Highlighter;
    static int CompleteEraser;
    static int PartialEraser;
    static int HighlighterCompleteEraser;
    static int HighlighterPartialEraser;
    static int PenStrokeSelector;
    static int BoxSelector;
    static int GlobalSelector;
    static int ShapeSelector;
    static int ShapeCircle;
    static int ShapeEllipse;
    static int ShapeSquare;
    static int ShapeRect;
    static int ShapeLine;
    static int ShapeRegular;
    static int ShapePolygon;
    static int LaserPointer;
    static int LaserPen;

private:
    SGToolTypeEnum(){}
    ~SGToolTypeEnum(){}
};

#endif // SGTOOLTYPEENUM_H
