#include "sghighlighterstrokeobject.h"
#include "sgnoteobjecttypeenum.h"

SGHighlighterStrokeObject::SGHighlighterStrokeObject(QUuid guid, float x, float y, float w, uint c, int z) : SGPolylineObject(guid, x, y, w, c, z){
    (*this).pointsx = new QVector<float>();
    (*this).pointsy = new QVector<float>();
    (*this).type = SGNoteObjectTypeEnum::HighlighterStroke;
}

SGHighlighterStrokeObject::~SGHighlighterStrokeObject(){
    delete (*this).pointsx;
    delete (*this).pointsy;
}
