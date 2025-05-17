#include "sgpolylinecollider.h"

SGPolylineCollider::SGPolylineCollider(){

}

SGPolylineCollider::~SGPolylineCollider(){
    if(pointsshared == false){
        delete pointsx;
        delete pointsy;
    }
}
