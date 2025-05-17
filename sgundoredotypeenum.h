#ifndef SGUNDOREDOTYPEENUM_H
#define SGUNDOREDOTYPEENUM_H

#include <QObject>

class SGUndoRedoTypeEnum : public QObject
{
    Q_OBJECT
public:
    static int Delete;
    static int Decode;
    static int Multidelete;
    static int Multidecode;
    static int Substitute;
    static int Multibackground;
    static int PageMoveDown;
    static int PageMoveUp;
    static int PageDelete;
    static int PageDecode;
    static int Template;
    static int Background;
    static int PenStrokeSelectorMove;
    static int PenStrokeSelectorResize;
    static int BoxResize;
    static int PenStrokeColour;
    static int PenStrokePenWidth;
    static int PenStrokeZIndex;
    static int BoxZIndex;
    static int TextboxAlign;
    static int TextboxTextColour;
    static int TextboxBackgroundColour;
    static int TextboxContent;
    static int LatexTextColour;
    static int LatexBackgroundColour;
    static int LatexContent;
    static int ImageContent;
    static int InternalLinkContent;
    static int ExternalLinkContent;
    static int ShapeOrigin;
    static int ShapeCircleRadius;
    static int ShapeEllipseAngle;
    static int ShapeEllipseRadius;
    static int ShapeSquareAngle;
    static int ShapeSquareSideLength;
    static int ShapeRectAngle;
    static int ShapeRectSides;
    static int ShapeLineEndpoint;
    static int ShapeRegularAngle;
    static int ShapeRegularRadius;
    static int ShapeRegularSideCount;
    static int ShapePolygonVertices;

private:
    SGUndoRedoTypeEnum(){}
    ~SGUndoRedoTypeEnum(){}
};

#endif // SGUNDOREDOTYPEENUM_H
