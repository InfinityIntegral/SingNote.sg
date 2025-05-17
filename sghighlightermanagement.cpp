#include "sghighlightermanagement.h"
#include "sgtouchinputmanagement.h"
#include "sggenerallibrary.h"
#include "sgnoteviewmanagement.h"
#include "sgcentralmanagement.h"
#include "sgnotemanagement.h"
#include "sgpolylinecollider.h"
#include "sgcollidermanagement.h"
#include "sgnoteobjecttypeenum.h"

SGHighlighterStrokeObject* SGHighlighterManagement::activehighlighterstroke = nullptr;
GLuint SGHighlighterManagement::vbo = 0;
int SGHighlighterManagement::vbors = 0;
int SGHighlighterManagement::vboms = 0;
GLuint SGHighlighterManagement::ebo = 0;
int SGHighlighterManagement::ebors = 0;
int SGHighlighterManagement::eboms = 0;
GLuint SGHighlighterManagement::vao = 0;
int SGHighlighterManagement::minp = 0;
int SGHighlighterManagement::maxp = 0;

void SGHighlighterManagement::startnewhighlighterstroke(){
    SGHighlighterManagement::activehighlighterstroke = new SGHighlighterStrokeObject(SGGeneralLibrary::GetNewGUID(), SGGeneralLibrary::DrawingTouchToNoteCoordsX(), SGGeneralLibrary::DrawingTouchToNoteCoordsY(), SGCentralManagement::activetoolwidth, SGCentralManagement::activetoolcolour, SGNoteManagement::highlighterstrokezindex);
    SGHighlighterManagement::minp = 0xFFFFFFF;
    SGHighlighterManagement::maxp = (-1) * 0xFFFFFFF;
    (*SGNoteViewManagement::highlighterstrokerenderer).makeCurrent();
    (*SGNoteViewManagement::highlighterstrokerenderer).glGenVertexArrays(1, &SGHighlighterManagement::vao);
    (*SGNoteViewManagement::highlighterstrokerenderer).glBindVertexArray(SGHighlighterManagement::vao);
    (*SGNoteViewManagement::highlighterstrokerenderer).glGenBuffers(1, &SGHighlighterManagement::vbo);
    (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_ARRAY_BUFFER, SGHighlighterManagement::vbo);
    (*SGNoteViewManagement::highlighterstrokerenderer).glBufferData(GL_ARRAY_BUFFER, 10 * 2 * sizeof(GLfloat), nullptr, GL_DYNAMIC_DRAW);
    SGHighlighterManagement::vbors = 0;
    SGHighlighterManagement::vboms = 10;
    (*SGNoteViewManagement::highlighterstrokerenderer).glGenBuffers(1, &SGHighlighterManagement::ebo);
    (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SGHighlighterManagement::ebo);
    (*SGNoteViewManagement::highlighterstrokerenderer).glBufferData(GL_ELEMENT_ARRAY_BUFFER, 10 * 3 * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
    SGHighlighterManagement::ebors = 0;
    SGHighlighterManagement::eboms = 10;
    (*SGNoteViewManagement::highlighterstrokerenderer).glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(0 * sizeof(GLfloat)));
    (*SGNoteViewManagement::highlighterstrokerenderer).glEnableVertexAttribArray(0);
    (*SGNoteViewManagement::highlighterstrokerenderer).update();
    (*SGNoteViewManagement::highlighterstrokerenderer).doneCurrent();
}

void SGHighlighterManagement::addtonewhighlighterstroke(){
    if((*(*SGHighlighterManagement::activehighlighterstroke).pointsx).size() > 0 && std::abs((*(*SGHighlighterManagement::activehighlighterstroke).pointsx)[(*(*SGHighlighterManagement::activehighlighterstroke).pointsx).size()-1] - SGGeneralLibrary::DrawingTouchToNoteCoordsX() + (*SGHighlighterManagement::activehighlighterstroke).originx) <= SGCentralManagement::writeprecision * 0.1f * (*SGHighlighterManagement::activehighlighterstroke).width && std::abs((*(*SGHighlighterManagement::activehighlighterstroke).pointsy)[(*(*SGHighlighterManagement::activehighlighterstroke).pointsy).size()-1] - SGGeneralLibrary::DrawingTouchToNoteCoordsY() + (*SGHighlighterManagement::activehighlighterstroke).originy) <= SGCentralManagement::writeprecision * 0.1f * (*SGHighlighterManagement::activehighlighterstroke).width){return;}
    (*(*SGHighlighterManagement::activehighlighterstroke).pointsx).push_back(SGGeneralLibrary::DrawingTouchToNoteCoordsX() - (*SGHighlighterManagement::activehighlighterstroke).originx);
    (*(*SGHighlighterManagement::activehighlighterstroke).pointsy).push_back(SGGeneralLibrary::DrawingTouchToNoteCoordsY() - (*SGHighlighterManagement::activehighlighterstroke).originy);
    int p = 1 + std::floor((((-1) * (*(*SGHighlighterManagement::activehighlighterstroke).pointsy)[(*(*SGHighlighterManagement::activehighlighterstroke).pointsy).size()-1]) - (*SGHighlighterManagement::activehighlighterstroke).originy - 0.05f * (*SGHighlighterManagement::activehighlighterstroke).width) / SGCentralManagement::pageh);
    if(SGHighlighterManagement::minp > p){SGHighlighterManagement::minp = p;}
    p = std::ceil((((-1) * (*(*SGHighlighterManagement::activehighlighterstroke).pointsy)[(*(*SGHighlighterManagement::activehighlighterstroke).pointsy).size()-1]) - (*SGHighlighterManagement::activehighlighterstroke).originy + 0.05f * (*SGHighlighterManagement::activehighlighterstroke).width) / SGCentralManagement::pageh);
    if(SGHighlighterManagement::maxp < p){SGHighlighterManagement::maxp = p;}
    if((*(*SGHighlighterManagement::activehighlighterstroke).pointsx).size() == 1){
        (*SGNoteViewManagement::highlighterstrokerenderer).makeCurrent();
        GLfloat newv[] = {-0.05f * (*SGHighlighterManagement::activehighlighterstroke).width + (*SGHighlighterManagement::activehighlighterstroke).originx, 0.05f * (*SGHighlighterManagement::activehighlighterstroke).width + (*SGHighlighterManagement::activehighlighterstroke).originy, 0.05f * (*SGHighlighterManagement::activehighlighterstroke).width + (*SGHighlighterManagement::activehighlighterstroke).originx, 0.05f * (*SGHighlighterManagement::activehighlighterstroke).width + (*SGHighlighterManagement::activehighlighterstroke).originy, -0.05f * (*SGHighlighterManagement::activehighlighterstroke).width + (*SGHighlighterManagement::activehighlighterstroke).originx, -0.05f * (*SGHighlighterManagement::activehighlighterstroke).width + (*SGHighlighterManagement::activehighlighterstroke).originy, 0.05f * (*SGHighlighterManagement::activehighlighterstroke).width + (*SGHighlighterManagement::activehighlighterstroke).originx, -0.05f * (*SGHighlighterManagement::activehighlighterstroke).width + (*SGHighlighterManagement::activehighlighterstroke).originy};
        GLuint newt[] = {0, 1, 2, 1, 2, 3};
        (*SGNoteViewManagement::highlighterstrokerenderer).glBindVertexArray(SGHighlighterManagement::vao);
        (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_ARRAY_BUFFER, SGHighlighterManagement::vbo);
        (*SGNoteViewManagement::highlighterstrokerenderer).glBufferSubData(GL_ARRAY_BUFFER, 0 * sizeof(GLfloat), 4 * 2 * sizeof(GLfloat), newv);
        SGHighlighterManagement::vbors = 4;
        (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SGHighlighterManagement::ebo);
        (*SGNoteViewManagement::highlighterstrokerenderer).glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0 * sizeof(GLuint), 2 * 3 * sizeof(GLuint), newt);
        SGHighlighterManagement::ebors = 2;
        (*SGNoteViewManagement::highlighterstrokerenderer).update();
        (*SGNoteViewManagement::highlighterstrokerenderer).doneCurrent();
    }
    else if((*(*SGHighlighterManagement::activehighlighterstroke).pointsx).size() == 2){
        (*SGNoteViewManagement::highlighterstrokerenderer).makeCurrent();
        float perpx;
        float perpy;
        SGGeneralLibrary::rotateplus90((*(*SGHighlighterManagement::activehighlighterstroke).pointsx)[1] - (*(*SGHighlighterManagement::activehighlighterstroke).pointsx)[0], (*(*SGHighlighterManagement::activehighlighterstroke).pointsy)[1] - (*(*SGHighlighterManagement::activehighlighterstroke).pointsy)[0], perpx, perpy);
        float offsetx;
        float offsety;
        SGGeneralLibrary::normalisevector(perpx, perpy, offsetx, offsety);
        offsetx *= (0.05f * SGCentralManagement::activetoolwidth);
        offsety *= (0.05f * SGCentralManagement::activetoolwidth);
        GLfloat newv[] = {(*SGHighlighterManagement::activehighlighterstroke).originx + (*(*SGHighlighterManagement::activehighlighterstroke).pointsx)[0] + offsetx, (*SGHighlighterManagement::activehighlighterstroke).originy + (*(*SGHighlighterManagement::activehighlighterstroke).pointsy)[0] + offsety, (*SGHighlighterManagement::activehighlighterstroke).originx + (*(*SGHighlighterManagement::activehighlighterstroke).pointsx)[0] - offsetx, (*SGHighlighterManagement::activehighlighterstroke).originy + (*(*SGHighlighterManagement::activehighlighterstroke).pointsy)[0] - offsety, (*SGHighlighterManagement::activehighlighterstroke).originx + (*(*SGHighlighterManagement::activehighlighterstroke).pointsx)[1] + offsetx, (*SGHighlighterManagement::activehighlighterstroke).originy + (*(*SGHighlighterManagement::activehighlighterstroke).pointsy)[1] + offsety, (*SGHighlighterManagement::activehighlighterstroke).originx + (*(*SGHighlighterManagement::activehighlighterstroke).pointsx)[1] - offsetx, (*SGHighlighterManagement::activehighlighterstroke).originy + (*(*SGHighlighterManagement::activehighlighterstroke).pointsy)[1] - offsety};
        GLuint newt[] = {0, 1, 2, 1, 2, 3};
        (*SGNoteViewManagement::highlighterstrokerenderer).glBindVertexArray(SGHighlighterManagement::vao);
        (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_ARRAY_BUFFER, SGHighlighterManagement::vbo);
        (*SGNoteViewManagement::highlighterstrokerenderer).glBufferSubData(GL_ARRAY_BUFFER, 0 * sizeof(GLfloat), 4 * 2 * sizeof(GLfloat), newv);
        SGHighlighterManagement::vbors = 4;
        (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SGHighlighterManagement::ebo);
        (*SGNoteViewManagement::highlighterstrokerenderer).glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0 * sizeof(GLuint), 2 * 3 * sizeof(GLuint), newt);
        SGHighlighterManagement::ebors = 2;
        (*SGNoteViewManagement::highlighterstrokerenderer).update();
        (*SGNoteViewManagement::highlighterstrokerenderer).doneCurrent();
    }
    else{
        (*SGNoteViewManagement::highlighterstrokerenderer).makeCurrent();
        float a1x = (*(*SGHighlighterManagement::activehighlighterstroke).pointsx)[(*(*SGHighlighterManagement::activehighlighterstroke).pointsx).size()-3];
        float a1y = (*(*SGHighlighterManagement::activehighlighterstroke).pointsy)[(*(*SGHighlighterManagement::activehighlighterstroke).pointsy).size()-3];
        float a2x = (*(*SGHighlighterManagement::activehighlighterstroke).pointsx)[(*(*SGHighlighterManagement::activehighlighterstroke).pointsx).size()-2];
        float a2y = (*(*SGHighlighterManagement::activehighlighterstroke).pointsy)[(*(*SGHighlighterManagement::activehighlighterstroke).pointsy).size()-2];
        float a3x = (*(*SGHighlighterManagement::activehighlighterstroke).pointsx)[(*(*SGHighlighterManagement::activehighlighterstroke).pointsx).size()-1];
        float a3y = (*(*SGHighlighterManagement::activehighlighterstroke).pointsy)[(*(*SGHighlighterManagement::activehighlighterstroke).pointsy).size()-1];
        float offset1x;
        float offset1y;
        float offset2x;
        float offset2y;
        float offset3x;
        float offset3y;
        (*SGNoteViewManagement::highlighterstrokerenderer).glBindVertexArray(SGHighlighterManagement::vao);
        if(SGHighlighterManagement::vboms <= SGHighlighterManagement::vbors + 3){SGGeneralLibrary::doublevbo(SGNoteViewManagement::highlighterstrokerenderer, SGHighlighterManagement::vbo, SGHighlighterManagement::vboms);}
        if(SGHighlighterManagement::eboms <= SGHighlighterManagement::ebors + 3){SGGeneralLibrary::doubleebo(SGNoteViewManagement::highlighterstrokerenderer, SGHighlighterManagement::ebo, SGHighlighterManagement::eboms);}
        (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_ARRAY_BUFFER, SGHighlighterManagement::vbo);
        (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SGHighlighterManagement::ebo);
        (*SGNoteViewManagement::highlighterstrokerenderer).glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(0 * sizeof(GLfloat)));
        (*SGNoteViewManagement::highlighterstrokerenderer).glEnableVertexAttribArray(0);
        GLfloat newv[5 * 2];
        GLuint newt[] = {(GLuint)(SGHighlighterManagement::vbors - 4), (GLuint)(SGHighlighterManagement::vbors - 3), (GLuint)(SGHighlighterManagement::vbors - 2), (GLuint)(SGHighlighterManagement::vbors - 3), (GLuint)(SGHighlighterManagement::vbors - 2), (GLuint)(SGHighlighterManagement::vbors - 1), (GLuint)(SGHighlighterManagement::vbors), (GLuint)(SGHighlighterManagement::vbors - 1), (GLuint)(SGHighlighterManagement::vbors - 2), (GLuint)(SGHighlighterManagement::vbors + 1), (GLuint)(SGHighlighterManagement::vbors), (GLuint)(SGHighlighterManagement::vbors - 1), (GLuint)(SGHighlighterManagement::vbors + 2), (GLuint)(SGHighlighterManagement::vbors + 1), (GLuint)(SGHighlighterManagement::vbors)};
        float perp1x;
        float perp1y;
        float perp2x;
        float perp2y;
        float perp3x;
        float perp3y;
        SGGeneralLibrary::rotateplus90(a2x - a1x, a2y - a1y, perp1x, perp1y);
        SGGeneralLibrary::rotateplus90(a3x - a2x, a3y - a2y, perp3x, perp3y);
        SGGeneralLibrary::normalisevector(perp1x, perp1y, offset1x, offset1y);
        SGGeneralLibrary::normalisevector(perp3x, perp3y, offset3x, offset3y);
        offset1x *= (0.05f * SGCentralManagement::activetoolwidth);
        offset1y *= (0.05f * SGCentralManagement::activetoolwidth);
        offset3x *= (0.05f * SGCentralManagement::activetoolwidth);
        offset3y *= (0.05f * SGCentralManagement::activetoolwidth);
        float det = SGGeneralLibrary::getdetsignonly(a1x, a1y, a2x, a2y, a3x, a3y);
        if((*(*SGHighlighterManagement::activehighlighterstroke).pointsx).size() > 3){
            float a0x = (*(*SGHighlighterManagement::activehighlighterstroke).pointsx)[(*(*SGHighlighterManagement::activehighlighterstroke).pointsx).size()-4];
            float a0y = (*(*SGHighlighterManagement::activehighlighterstroke).pointsy)[(*(*SGHighlighterManagement::activehighlighterstroke).pointsy).size()-4];
            float det0 = SGGeneralLibrary::getdetsignonly(a0x, a0y, a1x, a1y, a2x, a2y);
            if((det < 0 && det0 < 0) || (det >= 0 && det0 >= 0)){newt[2]++;}
        }
        perp2x = (0.5f) * (offset1x + offset3x);
        perp2y = (0.5f) * (offset1y + offset3y);
        SGGeneralLibrary::normalisevector(perp2x, perp2y, offset2x, offset2y);
        offset2x *= (0.05f * (*SGHighlighterManagement::activehighlighterstroke).width);
        offset2y *= (0.05f * (*SGHighlighterManagement::activehighlighterstroke).width);
        if(det < 0){
            newv[0] = a2x + offset1x + (*SGHighlighterManagement::activehighlighterstroke).originx;
            newv[1] = a2y + offset1y + (*SGHighlighterManagement::activehighlighterstroke).originy;
            newv[4] = a2x + offset3x + (*SGHighlighterManagement::activehighlighterstroke).originx;
            newv[5] = a2y + offset3y + (*SGHighlighterManagement::activehighlighterstroke).originy;
            newv[2] = a2x - offset2x + (*SGHighlighterManagement::activehighlighterstroke).originx;
            newv[3] = a2y - offset2y + (*SGHighlighterManagement::activehighlighterstroke).originy;
            newv[6] = a3x - offset3x + (*SGHighlighterManagement::activehighlighterstroke).originx;
            newv[7] = a3y - offset3y + (*SGHighlighterManagement::activehighlighterstroke).originy;
            newv[8] = a3x + offset3x + (*SGHighlighterManagement::activehighlighterstroke).originx;
            newv[9] = a3y + offset3y + (*SGHighlighterManagement::activehighlighterstroke).originy;
        }
        else{
            newv[0] = a2x - offset1x + (*SGHighlighterManagement::activehighlighterstroke).originx;
            newv[1] = a2y - offset1y + (*SGHighlighterManagement::activehighlighterstroke).originy;
            newv[4] = a2x - offset3x + (*SGHighlighterManagement::activehighlighterstroke).originx;
            newv[5] = a2y - offset3y + (*SGHighlighterManagement::activehighlighterstroke).originy;
            newv[2] = a2x + offset2x + (*SGHighlighterManagement::activehighlighterstroke).originx;
            newv[3] = a2y + offset2y + (*SGHighlighterManagement::activehighlighterstroke).originy;
            newv[6] = a3x + offset3x + (*SGHighlighterManagement::activehighlighterstroke).originx;
            newv[7] = a3y + offset3y + (*SGHighlighterManagement::activehighlighterstroke).originy;
            newv[8] = a3x - offset3x + (*SGHighlighterManagement::activehighlighterstroke).originx;
            newv[9] = a3y - offset3y + (*SGHighlighterManagement::activehighlighterstroke).originy;
        }
        (*SGNoteViewManagement::highlighterstrokerenderer).glBindVertexArray(SGHighlighterManagement::vao);
        (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_ARRAY_BUFFER, SGHighlighterManagement::vbo);
        (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SGHighlighterManagement::ebo);
        if(det >= 0 && (*(*SGHighlighterManagement::activehighlighterstroke).pointsx).size() == 3){
            GLfloat startv[] = {a1x - offset1x + (*SGHighlighterManagement::activehighlighterstroke).originx, a1y - offset1y + (*SGHighlighterManagement::activehighlighterstroke).originy, a1x + offset1x + (*SGHighlighterManagement::activehighlighterstroke).originx, a1y + offset1y + (*SGHighlighterManagement::activehighlighterstroke).originy};
            (*SGNoteViewManagement::highlighterstrokerenderer).glBufferSubData(GL_ARRAY_BUFFER, 0 * sizeof(GLfloat), 2 * 2 * sizeof(GLfloat), startv);
        }
        (*SGNoteViewManagement::highlighterstrokerenderer).glBufferSubData(GL_ARRAY_BUFFER, (SGHighlighterManagement::vbors - 2) * 2 * sizeof(GLfloat), 5 * 2 * sizeof(GLfloat), newv);
        (*SGNoteViewManagement::highlighterstrokerenderer).glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, (SGHighlighterManagement::ebors - 2) * 3 * sizeof(GLuint), 5 * 3 * sizeof(GLuint), newt);
        SGHighlighterManagement::vbors += 3;
        SGHighlighterManagement::ebors += 3;
        (*SGNoteViewManagement::highlighterstrokerenderer).update();
        (*SGNoteViewManagement::highlighterstrokerenderer).doneCurrent();
    }
}

void SGHighlighterManagement::endnewhighlighterstroke(){
    (*SGNoteViewManagement::highlighterstrokerenderer).makeCurrent();
    if(SGHighlighterManagement::minp < 1){SGHighlighterManagement::minp = 1;}
    if(SGHighlighterManagement::maxp < 1){SGHighlighterManagement::maxp = 1;}
    int pi = SGGeneralLibrary::getrenderingdataindex(SGHighlighterManagement::minp, SGHighlighterManagement::maxp);
    if((*SGNoteManagement::renderingdata).contains(pi) == false){(*SGNoteManagement::renderingdata)[pi] = new SGRenderingRange(SGHighlighterManagement::minp, SGHighlighterManagement::maxp);}
    unsigned long long k = (((unsigned long long)((uint)(*SGHighlighterManagement::activehighlighterstroke).zdepth)) << 32) | (uint)(*SGHighlighterManagement::activehighlighterstroke).colour;
    if((*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokelookuptable).contains(k) == false){
        (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokelookuptable)[k] = (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokezdepth).size();
        (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokezdepth).push_back((*SGHighlighterManagement::activehighlighterstroke).zdepth);
        (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokecolour).push_back((*SGHighlighterManagement::activehighlighterstroke).colour);
        GLuint vao0;
        (*SGNoteViewManagement::highlighterstrokerenderer).glGenVertexArrays(1, &vao0);
        (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevao).push_back(vao0);
        (*SGNoteViewManagement::highlighterstrokerenderer).glBindVertexArray(vao0);
        GLuint vbo0;
        (*SGNoteViewManagement::highlighterstrokerenderer).glGenBuffers(1, &vbo0);
        (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevbo).push_back(vbo0);
        (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_ARRAY_BUFFER, vbo0);
        (*SGNoteViewManagement::highlighterstrokerenderer).glBufferData(GL_ARRAY_BUFFER, 10 * 2 * sizeof(GLfloat), nullptr, GL_DYNAMIC_DRAW);
        GLfloat zerov[2] = {0.0f, 726.0f};
        (*SGNoteViewManagement::highlighterstrokerenderer).glBufferSubData(GL_ARRAY_BUFFER, 0 * 2 * sizeof(GLfloat), 1 * 2 * sizeof(GLfloat), zerov);
        (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevbors).push_back(1);
        (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevboms).push_back(10);
        GLuint ebo0;
        (*SGNoteViewManagement::highlighterstrokerenderer).glGenBuffers(1, &ebo0);
        (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokeebo).push_back(ebo0);
        (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo0);
        (*SGNoteViewManagement::highlighterstrokerenderer).glBufferData(GL_ELEMENT_ARRAY_BUFFER, 10 * 3 * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
        (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokeebors).push_back(0);
        (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokeeboms).push_back(10);
    }
    int di = (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokelookuptable)[k];
    while((*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevboms)[di] <= (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevbors)[di] + SGHighlighterManagement::vbors){SGGeneralLibrary::doublevbo(SGNoteViewManagement::highlighterstrokerenderer, (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevbo)[di], (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevboms)[di]);}
    while((*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokeeboms)[di] <= (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokeebors)[di] + SGHighlighterManagement::ebors){SGGeneralLibrary::doubleebo(SGNoteViewManagement::highlighterstrokerenderer, (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokeebo)[di], (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokeeboms)[di]);}

    GLuint vao1;
    (*SGNoteViewManagement::highlighterstrokerenderer).glGenVertexArrays(1, &vao1);
    (*SGNoteViewManagement::highlighterstrokerenderer).glBindVertexArray(vao1);
    GLuint ebo1;
    (*SGNoteViewManagement::highlighterstrokerenderer).glGenBuffers(1, &ebo1);
    (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_ARRAY_BUFFER, ebo1);
    (*SGNoteViewManagement::highlighterstrokerenderer).glBufferData(GL_ARRAY_BUFFER, SGHighlighterManagement::ebors * 3 * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
    (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_ARRAY_BUFFER, SGHighlighterManagement::ebo);
    (*SGNoteViewManagement::highlighterstrokerenderer).glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(GLuint), (void*)(0 * sizeof(GLuint)));
    (*SGNoteViewManagement::highlighterstrokerenderer).glEnableVertexAttribArray(0);
    (*SGNoteViewManagement::highlighterstrokerenderer).glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, ebo1);
    (*(*SGNoteViewManagement::highlighterstrokerenderer).transformfeedbackshaderprogramme).bind();
    (*SGNoteViewManagement::highlighterstrokerenderer).glUniform1ui((*SGNoteViewManagement::highlighterstrokerenderer).gvptransformfeedbackoffset, (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevbors)[di]);
    (*SGNoteViewManagement::highlighterstrokerenderer).glEnable(GL_RASTERIZER_DISCARD);
    (*SGNoteViewManagement::highlighterstrokerenderer).glBeginTransformFeedback(GL_POINTS);
    (*SGNoteViewManagement::highlighterstrokerenderer).glDrawArrays(GL_POINTS, 0, SGHighlighterManagement::ebors * 3);
    (*SGNoteViewManagement::highlighterstrokerenderer).glEndTransformFeedback();
    (*SGNoteViewManagement::highlighterstrokerenderer).glDisable(GL_RASTERIZER_DISCARD);

    (*SGHighlighterManagement::activehighlighterstroke).renderrangeindex = pi;
    (*SGHighlighterManagement::activehighlighterstroke).renderkey = di;
    (*SGNoteViewManagement::highlighterstrokerenderer).glBindVertexArray((*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevao)[di]);
    (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_ARRAY_BUFFER, (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevbo)[di]);
    (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokeebo)[di]);
    (*SGNoteViewManagement::highlighterstrokerenderer).glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(0 * sizeof(GLfloat)));
    (*SGNoteViewManagement::highlighterstrokerenderer).glEnableVertexAttribArray(0);
    (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_COPY_READ_BUFFER, SGHighlighterManagement::vbo);
    (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_COPY_WRITE_BUFFER, (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevbo)[di]);
    (*SGNoteViewManagement::highlighterstrokerenderer).glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0 * sizeof(GLfloat), (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevbors)[di] * 2 * sizeof(GLfloat), SGHighlighterManagement::vbors * 2 * sizeof(GLfloat));
    (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokevbors)[di] += SGHighlighterManagement::vbors;
    (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_COPY_READ_BUFFER, ebo1);
    (*SGNoteViewManagement::highlighterstrokerenderer).glBindBuffer(GL_COPY_WRITE_BUFFER, (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokeebo)[di]);
    (*SGNoteViewManagement::highlighterstrokerenderer).glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0 * 3 * sizeof(GLuint), (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokeebors)[di] * 3 * sizeof(GLuint), SGHighlighterManagement::ebors * 3 * sizeof(GLuint));
    (*SGHighlighterManagement::activehighlighterstroke).ebostartindex = (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokeebors)[di];
    (*SGHighlighterManagement::activehighlighterstroke).ebolength = SGHighlighterManagement::ebors;
    (*SGNoteViewManagement::highlighterstrokerenderer).glDeleteBuffers(1, &ebo1);
    (*(*(*SGNoteManagement::renderingdata)[pi]).highlighterstrokeebors)[di] += SGHighlighterManagement::ebors;
    (*SGNoteViewManagement::highlighterstrokerenderer).glDeleteVertexArrays(1, &SGHighlighterManagement::vao);
    (*SGNoteViewManagement::highlighterstrokerenderer).glDeleteBuffers(1, &SGHighlighterManagement::vbo);
    (*SGNoteViewManagement::highlighterstrokerenderer).glDeleteBuffers(1, &SGHighlighterManagement::ebo);
    SGHighlighterManagement::vbors = 0;
    SGHighlighterManagement::vboms = 0;
    SGHighlighterManagement::ebors = 0;
    SGHighlighterManagement::eboms = 0;
    SGHighlighterManagement::minp = 0;
    SGHighlighterManagement::maxp = 0;
    (*SGHighlighterManagement::activehighlighterstroke).dataindex = (*SGNoteManagement::notedata).size();
    (*SGNoteManagement::notedata).push_back(SGHighlighterManagement::activehighlighterstroke);
    (*SGNoteViewManagement::highlighterstrokerenderer).update();
    (*SGNoteViewManagement::highlighterstrokerenderer).doneCurrent();
    int rangeidx;
    int idx;
    SGPolylineCollider* col = SGColliderManagement::highlighterstrokegetcollider(SGHighlighterManagement::activehighlighterstroke);
    SGColliderManagement::registercollider(col, SGNoteObjectTypeEnum::HighlighterStroke, rangeidx, idx);
    (*SGHighlighterManagement::activehighlighterstroke).colliderrangeindex = rangeidx;
    (*SGHighlighterManagement::activehighlighterstroke).colliderindex = idx;
    SGHighlighterManagement::activehighlighterstroke = nullptr;
}
