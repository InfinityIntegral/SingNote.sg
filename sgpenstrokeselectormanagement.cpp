#include "sgpenstrokeselectormanagement.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"
#include "sgnoteviewmanagement.h"
#include <QDebug>

bool SGPenStrokeSelectorManagement::selectorexist = false;
float SGPenStrokeSelectorManagement::selectorx = 0.0f;
float SGPenStrokeSelectorManagement::selectory = 0.0f;
float SGPenStrokeSelectorManagement::selectorw = 0.0f;
float SGPenStrokeSelectorManagement::selectorh = 0.0f;
GLuint SGPenStrokeSelectorManagement::vao = 0;
GLuint SGPenStrokeSelectorManagement::vbo = 0;
GLuint SGPenStrokeSelectorManagement::ebo = 0;
GLuint SGPenStrokeSelectorManagement::resizevao = 0;
GLuint SGPenStrokeSelectorManagement::resizevbo = 0;
GLuint SGPenStrokeSelectorManagement::resizeebo = 0;
float SGPenStrokeSelectorManagement::initx = 0.0f;
float SGPenStrokeSelectorManagement::inity = 0.0f;
float SGPenStrokeSelectorManagement::inittouchx = 0.0f;
float SGPenStrokeSelectorManagement::inittouchy = 0.0f;
int SGPenStrokeSelectorManagement::selectortouchmode = 0;

void SGPenStrokeSelectorManagement::startselector(){
    SGPenStrokeSelectorManagement::selectortouchmode = 0;
    SGPenStrokeSelectorManagement::selectorexist = true;
    SGPenStrokeSelectorManagement::selectorx = SGGeneralLibrary::DrawingTouchToNoteCoordsX();
    SGPenStrokeSelectorManagement::selectory = SGGeneralLibrary::DrawingTouchToNoteCoordsY();
    SGPenStrokeSelectorManagement::selectorw = 0.0f;
    SGPenStrokeSelectorManagement::selectorh = 0.0f;

    (*SGNoteViewManagement::uirenderer).makeCurrent();
    (*SGNoteViewManagement::uirenderer).glGenVertexArrays(1, &SGPenStrokeSelectorManagement::vao);
    (*SGNoteViewManagement::uirenderer).glBindVertexArray(SGPenStrokeSelectorManagement::vao);
    GLfloat v[] = {0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f};
    GLuint t[] = {0, 1, 2, 1, 2, 3};
    (*SGNoteViewManagement::uirenderer).glGenBuffers(1, &SGPenStrokeSelectorManagement::vbo);
    (*SGNoteViewManagement::uirenderer).glBindBuffer(GL_ARRAY_BUFFER, SGPenStrokeSelectorManagement::vbo);
    (*SGNoteViewManagement::uirenderer).glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(GLfloat), v, GL_DYNAMIC_DRAW);
    (*SGNoteViewManagement::uirenderer).glGenBuffers(1, &SGPenStrokeSelectorManagement::ebo);
    (*SGNoteViewManagement::uirenderer).glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SGPenStrokeSelectorManagement::ebo);
    (*SGNoteViewManagement::uirenderer).glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * 3 * sizeof(GLuint), t, GL_DYNAMIC_DRAW);
    (*SGNoteViewManagement::uirenderer).glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(0 * sizeof(GLfloat)));
    (*SGNoteViewManagement::uirenderer).glEnableVertexAttribArray(0);
    (*SGNoteViewManagement::uirenderer).doneCurrent();
    (*SGNoteViewManagement::uirenderer).update();
}

void SGPenStrokeSelectorManagement::resizeselector(){
    SGPenStrokeSelectorManagement::selectorw = SGGeneralLibrary::DrawingTouchToNoteCoordsX() - SGPenStrokeSelectorManagement::selectorx;
    SGPenStrokeSelectorManagement::selectorh = SGGeneralLibrary::DrawingTouchToNoteCoordsY() - SGPenStrokeSelectorManagement::selectory;
    (*SGNoteViewManagement::uirenderer).update();
}

void SGPenStrokeSelectorManagement::activateselector(){
    if(SGPenStrokeSelectorManagement::selectorw < 0.0f){
        SGPenStrokeSelectorManagement::selectorx += SGPenStrokeSelectorManagement::selectorw;
        SGPenStrokeSelectorManagement::selectorw *= -1.0f;
    }
    if(SGPenStrokeSelectorManagement::selectorh < 0.0f){
        SGPenStrokeSelectorManagement::selectory += SGPenStrokeSelectorManagement::selectorh;
        SGPenStrokeSelectorManagement::selectorh *= -1.0f;
    }

    if(SGPenStrokeSelectorManagement::selectorw == 0.0f || SGPenStrokeSelectorManagement::selectorh == 0.0f){
        SGPenStrokeSelectorManagement::deleteselector();
        return;
    }

    (*SGNoteViewManagement::uirenderer).makeCurrent();
    (*SGNoteViewManagement::uirenderer).glGenVertexArrays(1, &SGPenStrokeSelectorManagement::resizevao);
    (*SGNoteViewManagement::uirenderer).glBindVertexArray(SGPenStrokeSelectorManagement::resizevao);
    GLfloat v[] = {0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f};
    GLuint t[] = {0, 1, 2, 1, 2, 3};
    (*SGNoteViewManagement::uirenderer).glGenBuffers(1, &SGPenStrokeSelectorManagement::resizevbo);
    (*SGNoteViewManagement::uirenderer).glBindBuffer(GL_ARRAY_BUFFER, SGPenStrokeSelectorManagement::resizevbo);
    (*SGNoteViewManagement::uirenderer).glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(GLfloat), v, GL_DYNAMIC_DRAW);
    (*SGNoteViewManagement::uirenderer).glGenBuffers(1, &SGPenStrokeSelectorManagement::resizeebo);
    (*SGNoteViewManagement::uirenderer).glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SGPenStrokeSelectorManagement::resizeebo);
    (*SGNoteViewManagement::uirenderer).glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * 3 * sizeof(GLuint), t, GL_DYNAMIC_DRAW);
    (*SGNoteViewManagement::uirenderer).glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(0 * sizeof(GLfloat)));
    (*SGNoteViewManagement::uirenderer).glEnableVertexAttribArray(0);
    (*SGNoteViewManagement::uirenderer).doneCurrent();
    (*SGNoteViewManagement::uirenderer).update();
}

void SGPenStrokeSelectorManagement::startmoveselector(){
    SGPenStrokeSelectorManagement::selectortouchmode = 1;
    SGPenStrokeSelectorManagement::inittouchx = SGGeneralLibrary::DrawingTouchToNoteCoordsX();
    SGPenStrokeSelectorManagement::inittouchy = SGGeneralLibrary::DrawingTouchToNoteCoordsY();
    SGPenStrokeSelectorManagement::initx = SGPenStrokeSelectorManagement::selectorx;
    SGPenStrokeSelectorManagement::inity = SGPenStrokeSelectorManagement::selectory;
}

void SGPenStrokeSelectorManagement::ongoingmoveselector(){
    SGPenStrokeSelectorManagement::selectorx = SGGeneralLibrary::DrawingTouchToNoteCoordsX() - SGPenStrokeSelectorManagement::inittouchx + SGPenStrokeSelectorManagement::initx;
    SGPenStrokeSelectorManagement::selectory = SGGeneralLibrary::DrawingTouchToNoteCoordsY() - SGPenStrokeSelectorManagement::inittouchy + SGPenStrokeSelectorManagement::inity;
}

void SGPenStrokeSelectorManagement::endmoveselector(){
    SGPenStrokeSelectorManagement::inittouchx = 0.0f;
    SGPenStrokeSelectorManagement::inittouchy = 0.0f;
    SGPenStrokeSelectorManagement::initx = 0.0f;
    SGPenStrokeSelectorManagement::inity = 0.0f;
}

void SGPenStrokeSelectorManagement::startresizeselector(){

}

void SGPenStrokeSelectorManagement::ongoingresizeselector(){

}

void SGPenStrokeSelectorManagement::endresizeselector(){

}

void SGPenStrokeSelectorManagement::deleteselector(){
    SGPenStrokeSelectorManagement::selectortouchmode = 0;
    SGPenStrokeSelectorManagement::selectorx = 0.0f;
    SGPenStrokeSelectorManagement::selectory = 0.0f;
    SGPenStrokeSelectorManagement::selectorw = 0.0f;
    SGPenStrokeSelectorManagement::selectorh = 0.0f;
    (*SGNoteViewManagement::uirenderer).makeCurrent();
    (*SGNoteViewManagement::uirenderer).glDeleteVertexArrays(1, &SGPenStrokeSelectorManagement::vao);
    SGPenStrokeSelectorManagement::vao = 0;
    (*SGNoteViewManagement::uirenderer).glDeleteBuffers(1, &SGPenStrokeSelectorManagement::vbo);
    SGPenStrokeSelectorManagement::vbo = 0;
    (*SGNoteViewManagement::uirenderer).glDeleteBuffers(1, &SGPenStrokeSelectorManagement::ebo);
    SGPenStrokeSelectorManagement::ebo = 0;
    (*SGNoteViewManagement::uirenderer).glDeleteVertexArrays(1, &SGPenStrokeSelectorManagement::resizevao);
    SGPenStrokeSelectorManagement::resizevao = 0;
    (*SGNoteViewManagement::uirenderer).glDeleteBuffers(1, &SGPenStrokeSelectorManagement::resizevbo);
    SGPenStrokeSelectorManagement::resizevbo = 0;
    (*SGNoteViewManagement::uirenderer).glDeleteBuffers(1, &SGPenStrokeSelectorManagement::resizeebo);
    SGPenStrokeSelectorManagement::resizeebo = 0;
    (*SGNoteViewManagement::uirenderer).doneCurrent();
}

bool SGPenStrokeSelectorManagement::drawingtouchinselector(){
    return false;
}

void SGPenStrokeSelectorManagement::touchstart(){
    if(SGPenStrokeSelectorManagement::vao != 0){SGPenStrokeSelectorManagement::deleteselector();}
    SGPenStrokeSelectorManagement::startselector();
}

void SGPenStrokeSelectorManagement::touchongoing(){
    if(SGPenStrokeSelectorManagement::selectortouchmode == 0){SGPenStrokeSelectorManagement::resizeselector();}
    else if(SGPenStrokeSelectorManagement::selectortouchmode == 1){SGPenStrokeSelectorManagement::ongoingmoveselector();}
}

void SGPenStrokeSelectorManagement::touchend(){
    if(SGPenStrokeSelectorManagement::selectortouchmode == 0){SGPenStrokeSelectorManagement::activateselector();}
    else if(SGPenStrokeSelectorManagement::selectortouchmode == 1){SGPenStrokeSelectorManagement::endmoveselector();}
}
