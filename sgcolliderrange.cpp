#include "sgcolliderrange.h"

SGColliderRange::SGColliderRange(int type, int y){
    (*this).y = y;
    (*this).type = type;
    (*this).penstrokes = new QVector<SGPolylineCollider*>();
    (*this).highlighterstrokes = new QVector<SGPolylineCollider*>();
}

SGColliderRange::~SGColliderRange(){
    for(int i=0; i<(*penstrokes).size(); i++){delete (*penstrokes)[i];}
    delete penstrokes;
    for(int i=0; i<(*highlighterstrokes).size(); i++){delete (*highlighterstrokes)[i];}
    delete highlighterstrokes;
}
