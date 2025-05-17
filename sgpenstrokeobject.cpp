#include "sgpenstrokeobject.h"
#include "sgnoteobjecttypeenum.h"

SGPenStrokeObject::SGPenStrokeObject(QUuid guid, float x, float y, float w, uint c, int z) : SGPolylineObject(guid, x, y, w, c, z){
    (*this).pointsx = new QVector<float>();
    (*this).pointsy = new QVector<float>();
    (*this).type = SGNoteObjectTypeEnum::PenStroke;
}

SGPenStrokeObject::~SGPenStrokeObject(){
    delete (*this).pointsx;
    delete (*this).pointsy;
}
