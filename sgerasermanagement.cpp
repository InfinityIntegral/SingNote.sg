#include "sgerasermanagement.h"
#include "sggenerallibrary.h"
#include "sgnoteviewmanagement.h"
#include "sgcentralmanagement.h"
#include "sgpolylinecollider.h"
#include "sgcollidermanagement.h"
#include "sgnotemanagement.h"
#include "sgtooltypeenum.h"
#include "sgnotesavingmanagement.h"

float SGEraserManagement::posx = 0.0f;
float SGEraserManagement::posy = 0.0f;
GLuint SGEraserManagement::vao = 0;
GLuint SGEraserManagement::vbo = 0;
GLuint SGEraserManagement::ebo = 0;

void SGEraserManagement::createeraser(){
    (*SGNoteViewManagement::uirenderer).makeCurrent();
    (*SGNoteViewManagement::uirenderer).glGenVertexArrays(1, &vao);
    (*SGNoteViewManagement::uirenderer).glBindVertexArray(vao);
    GLfloat newv[] = {-0.05f * SGCentralManagement::activetoolwidth, 0.05f * SGCentralManagement::activetoolwidth, 0.05f * SGCentralManagement::activetoolwidth, 0.05f * SGCentralManagement::activetoolwidth, -0.05f * SGCentralManagement::activetoolwidth, -0.05f * SGCentralManagement::activetoolwidth, 0.05f * SGCentralManagement::activetoolwidth, -0.05f * SGCentralManagement::activetoolwidth};
    (*SGNoteViewManagement::uirenderer).glGenBuffers(1, &vbo);
    (*SGNoteViewManagement::uirenderer).glBindBuffer(GL_ARRAY_BUFFER, vbo);
    (*SGNoteViewManagement::uirenderer).glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(GLfloat), newv, GL_DYNAMIC_DRAW);
    GLuint newt[] = {0, 1, 2, 1, 2, 3};
    (*SGNoteViewManagement::uirenderer).glGenBuffers(1, &ebo);
    (*SGNoteViewManagement::uirenderer).glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    (*SGNoteViewManagement::uirenderer).glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * 3 * sizeof(GLuint), newt, GL_DYNAMIC_DRAW);
    (*SGNoteViewManagement::uirenderer).glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(0 * sizeof(GLfloat)));
    (*SGNoteViewManagement::uirenderer).glEnableVertexAttribArray(0);
    (*SGNoteViewManagement::uirenderer).doneCurrent();
}

void SGEraserManagement::moveeraser(){
    posx = SGGeneralLibrary::DrawingTouchToNoteCoordsX();
    posy = SGGeneralLibrary::DrawingTouchToNoteCoordsY();
    (*SGNoteViewManagement::uirenderer).update();
    QVector<SGPolylineCollider*>* cl = nullptr;
    if(SGCentralManagement::activetooltype == SGToolTypeEnum::CompleteEraser || SGCentralManagement::activetooltype == SGToolTypeEnum::PartialEraser){
        cl = SGColliderManagement::circleintersectpenstroke(posx, posy, 0.05f * SGCentralManagement::activetoolwidth);
        for(int i=0; i<(*cl).size(); i++){
            if(SGCentralManagement::activetooltype == SGToolTypeEnum::PartialEraser){SGEraserManagement::generatepartialpenstrokes((SGPenStrokeObject*)((*(*cl)[i]).obj), posx, posy, 0.05f * SGCentralManagement::activetoolwidth);}
            SGEraserManagement::erasepenstroke((SGPenStrokeObject*)((*(*cl)[i]).obj));
        }
        delete cl;
        cl = nullptr;
        (*SGNoteViewManagement::penstrokerenderer).update();
    }
    cl = SGColliderManagement::circleintersecthighlighterstroke(posx, posy, 0.05f * SGCentralManagement::activetoolwidth);
    for(int i=0; i<(*cl).size(); i++){
        if(SGCentralManagement::activetooltype == SGToolTypeEnum::PartialEraser || SGCentralManagement::activetooltype == SGToolTypeEnum::HighlighterPartialEraser){SGEraserManagement::generatepartialhighlighterstrokes((SGHighlighterStrokeObject*)((*(*cl)[i]).obj), posx, posy, 0.05f * SGCentralManagement::activetoolwidth);}
        SGEraserManagement::erasehighlighterstroke((SGHighlighterStrokeObject*)((*(*cl)[i]).obj));
    }
    delete cl;
    (*SGNoteViewManagement::highlighterstrokerenderer).update();
}

void SGEraserManagement::deleteeraser(){
    (*SGNoteViewManagement::uirenderer).makeCurrent();
    posx = 0.0f;
    posy = 0.0f;
    (*SGNoteViewManagement::uirenderer).glDeleteVertexArrays(1, &vao);
    vao = 0;
    (*SGNoteViewManagement::uirenderer).glDeleteBuffers(1, &vbo);
    (*SGNoteViewManagement::uirenderer).glDeleteBuffers(1, &ebo);
    (*SGNoteViewManagement::uirenderer).doneCurrent();
}

void SGEraserManagement::erasepenstroke(SGPenStrokeObject* x){
    delete (*(*(*SGNoteManagement::collidersdata)[(*x).colliderrangeindex]).penstrokes)[(*x).colliderindex];
    (*(*(*SGNoteManagement::collidersdata)[(*x).colliderrangeindex]).penstrokes)[(*x).colliderindex] = nullptr;
    (*SGNoteViewManagement::penstrokerenderer).makeCurrent();
    GLuint zeroebo[(*x).ebolength * 3];
    memset(zeroebo, 0, (*x).ebolength * 3 * sizeof(GLuint));
    (*SGNoteViewManagement::penstrokerenderer).glBindVertexArray((*(*(*SGNoteManagement::renderingdata)[(*x).renderrangeindex]).penstrokevao)[((*x).renderkey)]);
    (*SGNoteViewManagement::penstrokerenderer).glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, (*x).ebostartindex * 3 * sizeof(GLuint), (*x).ebolength * 3 * sizeof(GLuint), zeroebo);
    (*SGNoteViewManagement::penstrokerenderer).doneCurrent();
    (*SGNoteManagement::notedata)[(*x).dataindex] = nullptr;
    delete x;
}

void SGEraserManagement::erasehighlighterstroke(SGHighlighterStrokeObject *x){
    delete (*(*(*SGNoteManagement::collidersdata)[(*x).colliderrangeindex]).highlighterstrokes)[(*x).colliderindex];
    (*(*(*SGNoteManagement::collidersdata)[(*x).colliderrangeindex]).highlighterstrokes)[(*x).colliderindex] = nullptr;
    (*SGNoteViewManagement::highlighterstrokerenderer).makeCurrent();
    GLuint zeroebo[(*x).ebolength * 3];
    memset(zeroebo, 0, (*x).ebolength * 3 * sizeof(GLuint));
    (*SGNoteViewManagement::highlighterstrokerenderer).glBindVertexArray((*(*(*SGNoteManagement::renderingdata)[(*x).renderrangeindex]).highlighterstrokevao)[((*x).renderkey)]);
    (*SGNoteViewManagement::highlighterstrokerenderer).glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, (*x).ebostartindex * 3 * sizeof(GLuint), (*x).ebolength * 3 * sizeof(GLuint), zeroebo);
    (*SGNoteViewManagement::highlighterstrokerenderer).doneCurrent();
    (*SGNoteManagement::notedata)[(*x).dataindex] = nullptr;
    delete x;
}

void SGEraserManagement::generatepartialpenstrokes(SGPenStrokeObject *o, float x, float y, float r){
    if((*(*o).pointsx).size() < 2){return;}
    QVector<float>* pointsx = new QVector<float>();
    QVector<float>* pointsy = new QVector<float>();
    for(int i=0; i<(*(*o).pointsx).size(); i++){
        if((i > 0 && i < (*(*o).pointsx).size() - 1 && SGColliderManagement::circleintersect3points(x, y, r, (*o).originx + (*(*o).pointsx)[i-1], (*o).originy + (*(*o).pointsy)[i-1], (*o).originx + (*(*o).pointsx)[i], (*o).originy + (*(*o).pointsy)[i], (*o).originx + (*(*o).pointsx)[i+1], (*o).originy + (*(*o).pointsy)[i+1], 0.05f * (*o).width) == false) || (i == 0 && SGColliderManagement::circleintersect2points(x, y, r, (*o).originx + (*(*o).pointsx)[i], (*o).originy + (*(*o).pointsy)[i], (*o).originx + (*(*o).pointsx)[i+1], (*o).originy + (*(*o).pointsy)[i+1], 0.05f * (*o).width) == false) || (i == (*(*o).pointsx).size() - 1 && SGColliderManagement::circleintersect2points(x, y, r, (*o).originx + (*(*o).pointsx)[i-1], (*o).originy + (*(*o).pointsy)[i-1], (*o).originx + (*(*o).pointsx)[i], (*o).originy + (*(*o).pointsy)[i], 0.05f * (*o).width) == false)){
            (*pointsx).push_back((*o).originx + (*(*o).pointsx)[i]);
            (*pointsy).push_back((*o).originy + (*(*o).pointsy)[i]);
        }
        else{
            if((*pointsx).size() == 0){continue;}
            SGPenStrokeObject* newobj = new SGPenStrokeObject(SGGeneralLibrary::GetNewGUID(), (*pointsx)[0], (*pointsy)[0], (*o).width, (*o).colour, (*o).zdepth);
            for(int j=0; j<(*pointsx).size(); j++){
                (*(*newobj).pointsx).push_back((*pointsx)[j] - (*pointsx)[0]);
                (*(*newobj).pointsy).push_back((*pointsy)[j] - (*pointsy)[0]);
            }
            SGNoteSavingManagement::initialisepenstroke(newobj);
            delete pointsx;
            delete pointsy;
            pointsx = new QVector<float>();
            pointsy = new QVector<float>();
        }
    }
    {
        if((*pointsx).size() > 0){
            SGPenStrokeObject* newobj = new SGPenStrokeObject(SGGeneralLibrary::GetNewGUID(), (*pointsx)[0], (*pointsy)[0], (*o).width, (*o).colour, (*o).zdepth);
            for(int i=0; i<(*pointsx).size(); i++){
                (*(*newobj).pointsx).push_back((*pointsx)[i] - (*pointsx)[0]);
                (*(*newobj).pointsy).push_back((*pointsy)[i] - (*pointsy)[0]);
            }
            SGNoteSavingManagement::initialisepenstroke(newobj);
        }
    }
    delete pointsx;
    delete pointsy;
}

void SGEraserManagement::generatepartialhighlighterstrokes(SGHighlighterStrokeObject *o, float x, float y, float r){
    if((*(*o).pointsx).size() < 2){return;}
    QVector<float>* pointsx = new QVector<float>();
    QVector<float>* pointsy = new QVector<float>();
    for(int i=0; i<(*(*o).pointsx).size(); i++){
        if((i > 0 && i < (*(*o).pointsx).size() - 1 && SGColliderManagement::circleintersect3points(x, y, r, (*o).originx + (*(*o).pointsx)[i-1], (*o).originy + (*(*o).pointsy)[i-1], (*o).originx + (*(*o).pointsx)[i], (*o).originy + (*(*o).pointsy)[i], (*o).originx + (*(*o).pointsx)[i+1], (*o).originy + (*(*o).pointsy)[i+1], 0.05f * (*o).width) == false) || (i == 0 && SGColliderManagement::circleintersect2points(x, y, r, (*o).originx + (*(*o).pointsx)[i], (*o).originy + (*(*o).pointsy)[i], (*o).originx + (*(*o).pointsx)[i+1], (*o).originy + (*(*o).pointsy)[i+1], 0.05f * (*o).width) == false) || (i == (*(*o).pointsx).size() - 1 && SGColliderManagement::circleintersect2points(x, y, r, (*o).originx + (*(*o).pointsx)[i-1], (*o).originy + (*(*o).pointsy)[i-1], (*o).originx + (*(*o).pointsx)[i], (*o).originy + (*(*o).pointsy)[i], 0.05f * (*o).width) == false)){
            (*pointsx).push_back((*o).originx + (*(*o).pointsx)[i]);
            (*pointsy).push_back((*o).originy + (*(*o).pointsy)[i]);
        }
        else{
            if((*pointsx).size() == 0){continue;}
            SGHighlighterStrokeObject* newobj = new SGHighlighterStrokeObject(SGGeneralLibrary::GetNewGUID(), (*pointsx)[0], (*pointsy)[0], (*o).width, (*o).colour, (*o).zdepth);
            for(int j=0; j<(*pointsx).size(); j++){
                (*(*newobj).pointsx).push_back((*pointsx)[j] - (*pointsx)[0]);
                (*(*newobj).pointsy).push_back((*pointsy)[j] - (*pointsy)[0]);
            }
            SGNoteSavingManagement::initialisehighlighterstroke(newobj);
            delete pointsx;
            delete pointsy;
            pointsx = new QVector<float>();
            pointsy = new QVector<float>();
        }
    }
    {
        if((*pointsx).size() > 0){
            SGHighlighterStrokeObject* newobj = new SGHighlighterStrokeObject(SGGeneralLibrary::GetNewGUID(), (*pointsx)[0], (*pointsy)[0], (*o).width, (*o).colour, (*o).zdepth);
            for(int i=0; i<(*pointsx).size(); i++){
                (*(*newobj).pointsx).push_back((*pointsx)[i] - (*pointsx)[0]);
                (*(*newobj).pointsy).push_back((*pointsy)[i] - (*pointsy)[0]);
            }
            SGNoteSavingManagement::initialisehighlighterstroke(newobj);
        }
    }
    delete pointsx;
    delete pointsy;
}
