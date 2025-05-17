#include "sgpagebackgroundobject.h"
#include "sgnoteviewmanagement.h"
#include "sgcentralmanagement.h"
#include "sgnoteobjecttypeenum.h"

SGPageBackgroundObject::SGPageBackgroundObject(int pn, QUuid guid) : SGPermanentObject(guid){
    (*this).pagenumber = pn;
    (*this).type = SGNoteObjectTypeEnum::Background;
}

SGPageBackgroundObject::~SGPageBackgroundObject(){

}
