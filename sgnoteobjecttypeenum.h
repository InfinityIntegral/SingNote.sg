#ifndef SGNOTEOBJECTTYPEENUM_H
#define SGNOTEOBJECTTYPEENUM_H

#include <QObject>

class SGNoteObjectTypeEnum : public QObject
{
    Q_OBJECT
public:
    static int Background;
    static int PenStroke;
    static int HighlighterStroke;
    static int Textbox;
    static int Latex;
    static int Image;
    static int InternalLink;
    static int ExternalLink;
    static int ShapeCircle;
    static int ShapeEllipse;
    static int ShapeSquare;
    static int ShapeRect;
    static int ShapeLine;
    static int ShapeRegular;
    static int ShapePolygon;

private:
    SGNoteObjectTypeEnum(){}
    ~SGNoteObjectTypeEnum(){}
};

#endif // SGNOTEOBJECTTYPEENUM_H
