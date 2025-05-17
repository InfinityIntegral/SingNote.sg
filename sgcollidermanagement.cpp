#include "sgcollidermanagement.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"
#include "sgnotemanagement.h"
#include "sgnoteobjecttypeenum.h"

SGPolylineCollider* SGColliderManagement::penstrokegetcollider(SGPenStrokeObject *x){
    SGPolylineCollider* c = new SGPolylineCollider();
    (*c).obj = x;
    (*c).pointsshared = true;
    (*c).originx = (*x).originx;
    (*c).originy = (*x).originy;
    (*c).w = 0.05f * (*x).width;
    (*c).pointsx = (*x).pointsx;
    (*c).pointsy = (*x).pointsy;
    (*c).l = SGGeneralLibrary::plusinf;
    (*c).r = SGGeneralLibrary::minusinf;
    (*c).u = SGGeneralLibrary::minusinf;
    (*c).d = SGGeneralLibrary::plusinf;
    for(int i=0; i<(*(*x).pointsx).size(); i++){
        if((*c).l > (*(*x).pointsx)[i] + (*x).originx - 0.05f * (*x).width){(*c).l = (*(*x).pointsx)[i] + (*x).originx - 0.05f * (*x).width;}
        if((*c).r < (*(*x).pointsx)[i] + (*x).originx + 0.05f * (*x).width){(*c).r = (*(*x).pointsx)[i] + (*x).originx + 0.05f * (*x).width;}
        if((*c).u < (*(*x).pointsy)[i] + (*x).originy + 0.05f * (*x).width){(*c).u = (*(*x).pointsy)[i] + (*x).originy + 0.05f * (*x).width;}
        if((*c).d > (*(*x).pointsy)[i] + (*x).originy - 0.05f * (*x).width){(*c).d = (*(*x).pointsy)[i] + (*x).originy - 0.05f * (*x).width;}
    }
    return c;
}

SGPolylineCollider* SGColliderManagement::highlighterstrokegetcollider(SGHighlighterStrokeObject *x){
    SGPolylineCollider* c = new SGPolylineCollider();
    (*c).obj = x;
    (*c).pointsshared = true;
    (*c).originx = (*x).originx;
    (*c).originy = (*x).originy;
    (*c).w = 0.05f * (*x).width;
    (*c).pointsx = (*x).pointsx;
    (*c).pointsy = (*x).pointsy;
    (*c).l = SGGeneralLibrary::plusinf;
    (*c).r = SGGeneralLibrary::minusinf;
    (*c).u = SGGeneralLibrary::minusinf;
    (*c).d = SGGeneralLibrary::plusinf;
    for(int i=0; i<(*(*x).pointsx).size(); i++){
        if((*c).l > (*(*x).pointsx)[i] + (*x).originx - 0.05f * (*x).width){(*c).l = (*(*x).pointsx)[i] + (*x).originx - 0.05f * (*x).width;}
        if((*c).r < (*(*x).pointsx)[i] + (*x).originx + 0.05f * (*x).width){(*c).r = (*(*x).pointsx)[i] + (*x).originx + 0.05f * (*x).width;}
        if((*c).u < (*(*x).pointsy)[i] + (*x).originy + 0.05f * (*x).width){(*c).u = (*(*x).pointsy)[i] + (*x).originy + 0.05f * (*x).width;}
        if((*c).d > (*(*x).pointsy)[i] + (*x).originy - 0.05f * (*x).width){(*c).d = (*(*x).pointsy)[i] + (*x).originy - 0.05f * (*x).width;}
    }
    return c;
}

void SGColliderManagement::registercollider(SGCollider *x, int type, int& rangeidx, int& idx){
    int c = 0;
    int y = 0;
    float l = (*x).l;
    if(l < -0.5f * SGCentralManagement::pagew){l = -0.5f * SGCentralManagement::pagew;}
    else if(l > 0.5f * SGCentralManagement::pagew){l = 0.5f * SGCentralManagement::pagew;}
    float r = (*x).r;
    if(r < -0.5f * SGCentralManagement::pagew){r = -0.5f * SGCentralManagement::pagew;}
    else if(r > 0.5f * SGCentralManagement::pagew){r = 0.5f * SGCentralManagement::pagew;}

    if(r - l < SGCentralManagement::pagew / 16.0f && (*x).u - (*x).d < SGCentralManagement::pageh / 16.0f){
        c = (int)((0.5f * SGCentralManagement::pagew + l) / (SGCentralManagement::pagew / 16.0f)) + 1;
        if(c < 1){c = 1;}
        else if(c > 15){c = 15;}
        y = (int)(((-1) * (*x).u) / (SGCentralManagement::pageh / 16.0f));
    }
    else if(r - l < SGCentralManagement::pagew / 8.0f && (*x).u - (*x).d < SGCentralManagement::pageh / 8.0f){
        c = (int)((0.5f * SGCentralManagement::pagew + l) / (SGCentralManagement::pagew / 8.0f)) + 16;
        if(c < 16){c = 16;}
        else if(c > 22){c = 22;}
        y = (int)(((-1) * (*x).u) / (SGCentralManagement::pageh / 8.0f));
    }
    else if(r - l < SGCentralManagement::pagew / 4.0f && (*x).u - (*x).d < SGCentralManagement::pageh / 4.0f){
        c = (int)((0.5f * SGCentralManagement::pagew + l) / (SGCentralManagement::pagew / 4.0f)) + 23;
        if(c < 23){c = 23;}
        else if(c > 25){c = 25;}
        y = (int)(((-1) * (*x).u) / (SGCentralManagement::pageh / 4.0f));
    }
    else if((*x).u - (*x).d < SGCentralManagement::pageh / 2.0f){
        c = 26;
        y = (int)(((-1) * (*x).u) / (SGCentralManagement::pageh / 2.0f));
    }
    else if((*x).u - (*x).d < SGCentralManagement::pageh){
        c = 27;
        y = (int)(((-1) * (*x).u) / (SGCentralManagement::pageh));
    }
    else{
        c = 28;
        y = 0;
    }
    if(y < 0){y = 0;}
    int ci = SGGeneralLibrary::getcolliderdataindex(c, y);
    if((*SGNoteManagement::collidersdata).contains(ci) == false){(*SGNoteManagement::collidersdata)[ci] = new SGColliderRange(c, y);}
    rangeidx = ci;
    if(type == SGNoteObjectTypeEnum::PenStroke){
        idx = (*(*(*SGNoteManagement::collidersdata)[ci]).penstrokes).size();
        (*(*(*SGNoteManagement::collidersdata)[ci]).penstrokes).push_back((SGPolylineCollider*)x);
    }
    else if(type == SGNoteObjectTypeEnum::HighlighterStroke){
        idx = (*(*(*SGNoteManagement::collidersdata)[ci]).highlighterstrokes).size();
        (*(*(*SGNoteManagement::collidersdata)[ci]).highlighterstrokes).push_back((SGPolylineCollider*)x);
    }
}

QVector<SGPolylineCollider*>* SGColliderManagement::circleintersectpenstroke(float x, float y, float r){
    QVector<SGPolylineCollider*>* o = new QVector<SGPolylineCollider*>();
    {
        int l0 = 1 + (int)((0.5f * SGCentralManagement::pagew + x - r) / (SGCentralManagement::pagew / 16.0f));
        int r0 = 15 + (-1) * (int)((0.5f * SGCentralManagement::pagew - x - r) / (SGCentralManagement::pagew / 16.0f));
        l0--;
        r0++;
        if(l0 < 1){l0 = 1;}
        else if(l0 > 15){l0 = 15;}
        if(r0 < 1){r0 = 1;}
        else if(r0 > 15){r0 = 15;}
        int u0 = (int)((-1.0f * y - r) / (SGCentralManagement::pageh / 16.0f));
        int d0 = (-1) * (int)((y - r) / (SGCentralManagement::pageh / 16.0f));
        u0--;
        d0++;
        if(u0 < 0){u0 = 0;}
        if(d0 < 0){d0 = 0;}
        for(int i=l0; i<=r0; i++){
            for(int j=u0; j<=d0; j++){
                SGColliderManagement::circleintersectpenstrokecolliderrange(x, y, r, SGGeneralLibrary::getcolliderdataindex(i, j), o);
            }
        }
    }
    {
        int l0 = 16 + (int)((0.5f * SGCentralManagement::pagew + x - r) / (SGCentralManagement::pagew / 8.0f));
        int r0 = 22 + (-1) * (int)((0.5f * SGCentralManagement::pagew - x - r) / (SGCentralManagement::pagew / 8.0f));
        l0--;
        r0++;
        if(l0 < 16){l0 = 16;}
        else if(l0 > 22){l0 = 22;}
        if(r0 < 16){r0 = 16;}
        else if(r0 > 22){r0 = 22;}
        int u0 = (int)((-1.0f * y - r) / (SGCentralManagement::pageh / 8.0f));
        int d0 = (-1) * (int)((y - r) / (SGCentralManagement::pageh / 8.0f));
        u0--;
        d0++;
        if(u0 < 0){u0 = 0;}
        if(d0 < 0){d0 = 0;}
        for(int i=l0; i<=r0; i++){
            for(int j=u0; j<=d0; j++){
                SGColliderManagement::circleintersectpenstrokecolliderrange(x, y, r, SGGeneralLibrary::getcolliderdataindex(i, j), o);
            }
        }
    }
    {
        int l0 = 23 + (int)((0.5f * SGCentralManagement::pagew + x - r) / (SGCentralManagement::pagew / 4.0f));
        int r0 = 25 + (-1) * (int)((0.5f * SGCentralManagement::pagew - x - r) / (SGCentralManagement::pagew / 4.0f));
        l0--;
        r0++;
        if(l0 < 23){l0 = 23;}
        else if(l0 > 25){l0 = 25;}
        if(r0 < 23){r0 = 23;}
        else if(r0 > 25){r0 = 25;}
        int u0 = (int)((-1.0f * y - r) / (SGCentralManagement::pageh / 4.0f));
        int d0 = (-1) * (int)((y - r) / (SGCentralManagement::pageh / 4.0f));
        u0--;
        d0++;
        if(u0 < 0){u0 = 0;}
        if(d0 < 0){d0 = 0;}
        for(int i=l0; i<=r0; i++){
            for(int j=u0; j<=d0; j++){
                SGColliderManagement::circleintersectpenstrokecolliderrange(x, y, r, SGGeneralLibrary::getcolliderdataindex(i, j), o);
            }
        }
    }
    {
        int u0 = (int)((-1.0f * y - r) / (SGCentralManagement::pageh / 2.0f));
        int d0 = (-1) * (int)((y - r) / (SGCentralManagement::pageh / 2.0f));
        u0--;
        d0++;
        if(u0 < 0){u0 = 0;}
        if(d0 < 0){d0 = 0;}
        for(int j=u0; j<=d0; j++){
            SGColliderManagement::circleintersectpenstrokecolliderrange(x, y, r, SGGeneralLibrary::getcolliderdataindex(26, j), o);
        }
    }
    {
        int u0 = (int)((-1.0f * y - r) / SGCentralManagement::pageh);
        int d0 = (-1) * (int)((y - r) / SGCentralManagement::pageh);
        u0--;
        d0++;
        if(u0 < 0){u0 = 0;}
        if(d0 < 0){d0 = 0;}
        for(int j=u0; j<=d0; j++){
            SGColliderManagement::circleintersectpenstrokecolliderrange(x, y, r, SGGeneralLibrary::getcolliderdataindex(27, j), o);
        }
    }
    {
        SGColliderManagement::circleintersectpenstrokecolliderrange(x, y, r, SGGeneralLibrary::getcolliderdataindex(28, 0), o);
    }
    return o;
}

QVector<SGPolylineCollider*>* SGColliderManagement::circleintersecthighlighterstroke(float x, float y, float r){
    QVector<SGPolylineCollider*>* o = new QVector<SGPolylineCollider*>();
    {
        int l0 = 1 + (int)((0.5f * SGCentralManagement::pagew + x - r) / (SGCentralManagement::pagew / 16.0f));
        int r0 = 15 + (-1) * (int)((0.5f * SGCentralManagement::pagew - x - r) / (SGCentralManagement::pagew / 16.0f));
        l0--;
        r0++;
        if(l0 < 1){l0 = 1;}
        else if(l0 > 15){l0 = 15;}
        if(r0 < 1){r0 = 1;}
        else if(r0 > 15){r0 = 15;}
        int u0 = (int)((-1.0f * y - r) / (SGCentralManagement::pageh / 16.0f));
        int d0 = (-1) * (int)((y - r) / (SGCentralManagement::pageh / 16.0f));
        u0--;
        d0++;
        if(u0 < 0){u0 = 0;}
        if(d0 < 0){d0 = 0;}
        for(int i=l0; i<=r0; i++){
            for(int j=u0; j<=d0; j++){
                SGColliderManagement::circleintersecthighlighterstrokecolliderrange(x, y, r, SGGeneralLibrary::getcolliderdataindex(i, j), o);
            }
        }
    }
    {
        int l0 = 16 + (int)((0.5f * SGCentralManagement::pagew + x - r) / (SGCentralManagement::pagew / 8.0f));
        int r0 = 22 + (-1) * (int)((0.5f * SGCentralManagement::pagew - x - r) / (SGCentralManagement::pagew / 8.0f));
        l0--;
        r0++;
        if(l0 < 16){l0 = 16;}
        else if(l0 > 22){l0 = 22;}
        if(r0 < 16){r0 = 16;}
        else if(r0 > 22){r0 = 22;}
        int u0 = (int)((-1.0f * y - r) / (SGCentralManagement::pageh / 8.0f));
        int d0 = (-1) * (int)((y - r) / (SGCentralManagement::pageh / 8.0f));
        u0--;
        d0++;
        if(u0 < 0){u0 = 0;}
        if(d0 < 0){d0 = 0;}
        for(int i=l0; i<=r0; i++){
            for(int j=u0; j<=d0; j++){
                SGColliderManagement::circleintersecthighlighterstrokecolliderrange(x, y, r, SGGeneralLibrary::getcolliderdataindex(i, j), o);
            }
        }
    }
    {
        int l0 = 23 + (int)((0.5f * SGCentralManagement::pagew + x - r) / (SGCentralManagement::pagew / 4.0f));
        int r0 = 25 + (-1) * (int)((0.5f * SGCentralManagement::pagew - x - r) / (SGCentralManagement::pagew / 4.0f));
        l0--;
        r0++;
        if(l0 < 23){l0 = 23;}
        else if(l0 > 25){l0 = 25;}
        if(r0 < 23){r0 = 23;}
        else if(r0 > 25){r0 = 25;}
        int u0 = (int)((-1.0f * y - r) / (SGCentralManagement::pageh / 4.0f));
        int d0 = (-1) * (int)((y - r) / (SGCentralManagement::pageh / 4.0f));
        u0--;
        d0++;
        if(u0 < 0){u0 = 0;}
        if(d0 < 0){d0 = 0;}
        for(int i=l0; i<=r0; i++){
            for(int j=u0; j<=d0; j++){
                SGColliderManagement::circleintersecthighlighterstrokecolliderrange(x, y, r, SGGeneralLibrary::getcolliderdataindex(i, j), o);
            }
        }
    }
    {
        int u0 = (int)((-1.0f * y - r) / (SGCentralManagement::pageh / 2.0f));
        int d0 = (-1) * (int)((y - r) / (SGCentralManagement::pageh / 2.0f));
        u0--;
        d0++;
        if(u0 < 0){u0 = 0;}
        if(d0 < 0){d0 = 0;}
        for(int j=u0; j<=d0; j++){
            SGColliderManagement::circleintersecthighlighterstrokecolliderrange(x, y, r, SGGeneralLibrary::getcolliderdataindex(26, j), o);
        }
    }
    {
        int u0 = (int)((-1.0f * y - r) / SGCentralManagement::pageh);
        int d0 = (-1) * (int)((y - r) / SGCentralManagement::pageh);
        u0--;
        d0++;
        if(u0 < 0){u0 = 0;}
        if(d0 < 0){d0 = 0;}
        for(int j=u0; j<=d0; j++){
            SGColliderManagement::circleintersecthighlighterstrokecolliderrange(x, y, r, SGGeneralLibrary::getcolliderdataindex(27, j), o);
        }
    }
    {
        SGColliderManagement::circleintersecthighlighterstrokecolliderrange(x, y, r, SGGeneralLibrary::getcolliderdataindex(28, 0), o);
    }
    return o;
}

void SGColliderManagement::circleintersectpenstrokecolliderrange(float x, float y, float r, int ri, QVector<SGPolylineCollider *> *o){
    if((*SGNoteManagement::collidersdata).contains(ri) == false){return;}
    for(int i=0; i<(*(*(*SGNoteManagement::collidersdata)[ri]).penstrokes).size(); i++){
        if(SGColliderManagement::circleintersectpolylinecollider(x, y, r, (*(*(*SGNoteManagement::collidersdata)[ri]).penstrokes)[i])){(*o).push_back((*(*(*SGNoteManagement::collidersdata)[ri]).penstrokes)[i]);}
    }
}

void SGColliderManagement::circleintersecthighlighterstrokecolliderrange(float x, float y, float r, int ri, QVector<SGPolylineCollider *> *o){
    if((*SGNoteManagement::collidersdata).contains(ri) == false){return;}
    for(int i=0; i<(*(*(*SGNoteManagement::collidersdata)[ri]).highlighterstrokes).size(); i++){
        if(SGColliderManagement::circleintersectpolylinecollider(x, y, r, (*(*(*SGNoteManagement::collidersdata)[ri]).highlighterstrokes)[i])){(*o).push_back((*(*(*SGNoteManagement::collidersdata)[ri]).highlighterstrokes)[i]);}
    }
}

bool SGColliderManagement::circleintersectpolylinecollider(float x, float y, float r, SGPolylineCollider *c){
    if(c == nullptr){return false;}
    if(x + r < (*c).l || x - r > (*c).r || y + r < (*c).d || y - r > (*c).u){return false;}
    if((*(*c).pointsx).size() == 1){return true;}
    {
        float x0 = (*c).originx + (*(*c).pointsx)[0];
        float y0 = (*c).originy + (*(*c).pointsy)[0];
        if((x - x0) * (x - x0) + (y - y0) * (y - y0) <= r * r){return true;}
        x0 = (*c).originx + (*(*c).pointsx)[(*(*c).pointsx).size() - 1];
        y0 = (*c).originy + (*(*c).pointsy)[(*(*c).pointsx).size() - 1];
        if((x - x0) * (x - x0) + (y - y0) * (y - y0) <= r * r){return true;}
        x0 = (*c).originx + (*(*c).pointsx)[((*(*c).pointsx).size() - 1) / 2];
        y0 = (*c).originy + (*(*c).pointsy)[((*(*c).pointsx).size() - 1) / 2];
        if((x - x0) * (x - x0) + (y - y0) * (y - y0) <= r * r){return true;}
        x0 = (*c).originx + (*(*c).pointsx)[((*(*c).pointsx).size() - 1) / 4];
        y0 = (*c).originy + (*(*c).pointsy)[((*(*c).pointsx).size() - 1) / 4];
        if((x - x0) * (x - x0) + (y - y0) * (y - y0) <= r * r){return true;}
        x0 = (*c).originx + (*(*c).pointsx)[3 * ((*(*c).pointsx).size() - 1) / 4];
        y0 = (*c).originy + (*(*c).pointsy)[3 * ((*(*c).pointsx).size() - 1) / 4];
        if((x - x0) * (x - x0) + (y - y0) * (y - y0) <= r * r){return true;}
    }
    for(int i=0; i<(*(*c).pointsx).size(); i++){
        float x0 = (*c).originx + (*(*c).pointsx)[i];
        float y0 = (*c).originy + (*(*c).pointsy)[i];
        if((x - x0) * (x - x0) + (y - y0) * (y - y0) <= r * r){return true;}
    }
    for(int i=0; i<(*(*c).pointsx).size()-1; i++){
        float x1 = x - (*c).originx;
        float y1 = y - (*c).originy;
        float x2 = (*(*c).pointsx)[i];
        float y2 = (*(*c).pointsy)[i];
        float x3 = (*(*c).pointsx)[i + 1];
        float y3 = (*(*c).pointsy)[i + 1];
        float det = ((x1 - x2) * (x3 - x2) + (y1 - y2) * (y3 - y2)) / ((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
        float dist = ((x3 - x2) * (y1 - y2) - (y3 - y2) * (x1 - x2)) * ((x3 - x2) * (y1 - y2) - (y3 - y2) * (x1 - x2)) / ((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
        if(dist <= (r + (*c).w) * (r + (*c).w) && det >= 0 && det <= 1){return true;}
    }
    return false;
}

bool SGColliderManagement::circleintersect3points(float x, float y, float r, float x1, float y1, float x2, float y2, float x3, float y3, float w){
    bool istouching = false;
    float x01 = x1 - x;
    float y01 = y1 - y;
    float x02 = x2 - x;
    float y02 = y2 - y;
    float x03 = x3 - x;
    float y03 = y3 - y;
    if(x01 * x01 + y01 * y01 <= r * r || x02 * x02 + y02 * y02 <= r * r || x03 * x03 + y03 * y03 <= r * r){return true;}
    {
        float det = (x01 * (x01 - x02) + y01 * (y01 - y02)) / ((x02 - x01) * (x02 - x01) + (y02 - y01) * (y02 - y01));
        float dist = ((x01 - x02) * y01 - (y01 - y02) * x01) * ((x01 - x02) * y01 - (y01 - y02) * x01) / ((x02 - x01) * (x02 - x01) + (y02 - y01) * (y02 - y01));
        if(dist <= (r + w) * (r + w) && det >= 0 && det <= 1){istouching = true;}
    }
    {
        float det = (x02 * (x02 - x03) + y02 * (y02 - y03)) / ((x03 - x02) * (x03 - x02) + (y03 - y02) * (y03 - y02));
        float dist = ((x02 - x03) * y02 - (y02 - y03) * x02) * ((x02 - x03) * y02 - (y02 - y03) * x02) / ((x03 - x02) * (x03 - x02) + (y03 - y02) * (y03 - y02));
        if(dist < (r + w) * (r + w) && det >= 0 && det <= 1){istouching = true;}
    }
    return istouching;
}

bool SGColliderManagement::circleintersect2points(float x, float y, float r, float x1, float y1, float x2, float y2, float w){
    bool istouching = false;
    float x01 = x1 - x;
    float y01 = y1 - y;
    float x02 = x2 - x;
    float y02 = y2 - y;
    if(x01 * x01 + y01 * y01 <= r * r || x02 * x02 + y02 * y02 <= r * r){return true;}
    {
        float det = (x01 * (x01 - x02) + y01 * (y01 - y02)) / ((x02 - x01) * (x02 - x01) + (y02 - y01) * (y02 - y01));
        float dist = ((x01 - x02) * y01 - (y01 - y02) * x01) * ((x01 - x02) * y01 - (y01 - y02) * x01) / ((x02 - x01) * (x02 - x01) + (y02 - y01) * (y02 - y01));
        if(dist <= (r + w) * (r + w) && det >= 0 && det <= 1){istouching = true;}
    }
    return istouching;
}
