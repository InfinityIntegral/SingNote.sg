#include "sgcentralmanagement.h"
#include "sgpolylineobject.h"

SGPolylineObject::SGPolylineObject(QUuid guid, float x, float y, float w, uint c, int z) : SGPermanentObject(guid){
    (*this).originx = x;
    (*this).originy = y;
    (*this).width = SGCentralManagement::activetoolwidth;
    (*this).width = w;
    (*this).colour = c;
    (*this).zdepth = z;
}
