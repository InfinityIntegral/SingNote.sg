#include "sgpenmanagement.h"
#include "sgtouchinputmanagement.h"
#include "sggenerallibrary.h"
#include "sgnoteviewmanagement.h"
#include "sgcentralmanagement.h"
#include "sgnotemanagement.h"
#include "sgpolylinecollider.h"
#include "sgcollidermanagement.h"
#include "sgnoteobjecttypeenum.h"

SGPenStrokeObject* SGPenManagement::activepenstroke = nullptr;
GLuint SGPenManagement::vbo = 0;
int SGPenManagement::vbors = 0;
int SGPenManagement::vboms = 0;
GLuint SGPenManagement::ebo = 0;
int SGPenManagement::ebors = 0;
int SGPenManagement::eboms = 0;
GLuint SGPenManagement::vao = 0;
int SGPenManagement::minp = 0;
int SGPenManagement::maxp = 0;

void SGPenManagement::startnewpenstroke(){
    SGPenManagement::activepenstroke = new SGPenStrokeObject(SGGeneralLibrary::GetNewGUID(), SGGeneralLibrary::DrawingTouchToNoteCoordsX(), SGGeneralLibrary::DrawingTouchToNoteCoordsY(), SGCentralManagement::activetoolwidth, SGCentralManagement::activetoolcolour, SGNoteManagement::penstrokezindex);
    SGPenManagement::minp = 0xFFFFFFF;
    SGPenManagement::maxp = (-1) * 0xFFFFFFF;
    (*SGNoteViewManagement::penstrokerenderer).makeCurrent();
    (*SGNoteViewManagement::penstrokerenderer).glGenVertexArrays(1, &SGPenManagement::vao);
    (*SGNoteViewManagement::penstrokerenderer).glBindVertexArray(SGPenManagement::vao);
    (*SGNoteViewManagement::penstrokerenderer).glGenBuffers(1, &SGPenManagement::vbo);
    (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_ARRAY_BUFFER, SGPenManagement::vbo);
    (*SGNoteViewManagement::penstrokerenderer).glBufferData(GL_ARRAY_BUFFER, 10 * 2 * sizeof(GLfloat), nullptr, GL_DYNAMIC_DRAW);
    SGPenManagement::vbors = 0;
    SGPenManagement::vboms = 10;
    (*SGNoteViewManagement::penstrokerenderer).glGenBuffers(1, &SGPenManagement::ebo);
    (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SGPenManagement::ebo);
    (*SGNoteViewManagement::penstrokerenderer).glBufferData(GL_ELEMENT_ARRAY_BUFFER, 10 * 3 * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
    SGPenManagement::ebors = 0;
    SGPenManagement::eboms = 10;
    (*SGNoteViewManagement::penstrokerenderer).glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(0 * sizeof(GLfloat)));
    (*SGNoteViewManagement::penstrokerenderer).glEnableVertexAttribArray(0);
    (*SGNoteViewManagement::penstrokerenderer).update();
    (*SGNoteViewManagement::penstrokerenderer).doneCurrent();
}

void SGPenManagement::addtonewpenstroke(){
    if((*(*SGPenManagement::activepenstroke).pointsx).size() > 0 && std::abs((*(*SGPenManagement::activepenstroke).pointsx)[(*(*SGPenManagement::activepenstroke).pointsx).size()-1] - SGGeneralLibrary::DrawingTouchToNoteCoordsX() + (*SGPenManagement::activepenstroke).originx) <= SGCentralManagement::writeprecision * 0.1f * (*SGPenManagement::activepenstroke).width && std::abs((*(*SGPenManagement::activepenstroke).pointsy)[(*(*SGPenManagement::activepenstroke).pointsy).size()-1] - SGGeneralLibrary::DrawingTouchToNoteCoordsY() + (*SGPenManagement::activepenstroke).originy) <= SGCentralManagement::writeprecision * 0.1f * (*SGPenManagement::activepenstroke).width){return;}
    (*(*SGPenManagement::activepenstroke).pointsx).push_back(SGGeneralLibrary::DrawingTouchToNoteCoordsX() - (*SGPenManagement::activepenstroke).originx);
    (*(*SGPenManagement::activepenstroke).pointsy).push_back(SGGeneralLibrary::DrawingTouchToNoteCoordsY() - (*SGPenManagement::activepenstroke).originy);
    int p = 1 + std::floor((((-1) * (*(*SGPenManagement::activepenstroke).pointsy)[(*(*SGPenManagement::activepenstroke).pointsy).size()-1]) - (*SGPenManagement::activepenstroke).originy - 0.05f * (*SGPenManagement::activepenstroke).width) / SGCentralManagement::pageh);
    if(SGPenManagement::minp > p){SGPenManagement::minp = p;}
    p = std::ceil((((-1) * (*(*SGPenManagement::activepenstroke).pointsy)[(*(*SGPenManagement::activepenstroke).pointsy).size()-1]) - (*SGPenManagement::activepenstroke).originy + 0.05f * (*SGPenManagement::activepenstroke).width) / SGCentralManagement::pageh);
    if(SGPenManagement::maxp < p){SGPenManagement::maxp = p;}
    if((*(*SGPenManagement::activepenstroke).pointsx).size() == 1){
        (*SGNoteViewManagement::penstrokerenderer).makeCurrent();
        GLfloat newv[] = {-0.05f * (*SGPenManagement::activepenstroke).width + (*SGPenManagement::activepenstroke).originx, 0.05f * (*SGPenManagement::activepenstroke).width + (*SGPenManagement::activepenstroke).originy, 0.05f * (*SGPenManagement::activepenstroke).width + (*SGPenManagement::activepenstroke).originx, 0.05f * (*SGPenManagement::activepenstroke).width + (*SGPenManagement::activepenstroke).originy, -0.05f * (*SGPenManagement::activepenstroke).width + (*SGPenManagement::activepenstroke).originx, -0.05f * (*SGPenManagement::activepenstroke).width + (*SGPenManagement::activepenstroke).originy, 0.05f * (*SGPenManagement::activepenstroke).width + (*SGPenManagement::activepenstroke).originx, -0.05f * (*SGPenManagement::activepenstroke).width + (*SGPenManagement::activepenstroke).originy};
        GLuint newt[] = {0, 1, 2, 1, 2, 3};
        (*SGNoteViewManagement::penstrokerenderer).glBindVertexArray(SGPenManagement::vao);
        (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_ARRAY_BUFFER, SGPenManagement::vbo);
        (*SGNoteViewManagement::penstrokerenderer).glBufferSubData(GL_ARRAY_BUFFER, 0 * sizeof(GLfloat), 4 * 2 * sizeof(GLfloat), newv);
        SGPenManagement::vbors = 4;
        (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SGPenManagement::ebo);
        (*SGNoteViewManagement::penstrokerenderer).glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0 * sizeof(GLuint), 2 * 3 * sizeof(GLuint), newt);
        SGPenManagement::ebors = 2;
        (*SGNoteViewManagement::penstrokerenderer).update();
        (*SGNoteViewManagement::penstrokerenderer).doneCurrent();
    }
    else if((*(*SGPenManagement::activepenstroke).pointsx).size() == 2){
        (*SGNoteViewManagement::penstrokerenderer).makeCurrent();
        float perpx;
        float perpy;
        SGGeneralLibrary::rotateplus90((*(*SGPenManagement::activepenstroke).pointsx)[1] - (*(*SGPenManagement::activepenstroke).pointsx)[0], (*(*SGPenManagement::activepenstroke).pointsy)[1] - (*(*SGPenManagement::activepenstroke).pointsy)[0], perpx, perpy);
        float offsetx;
        float offsety;
        SGGeneralLibrary::normalisevector(perpx, perpy, offsetx, offsety);
        offsetx *= (0.05f * SGCentralManagement::activetoolwidth);
        offsety *= (0.05f * SGCentralManagement::activetoolwidth);
        GLfloat newv[] = {(*SGPenManagement::activepenstroke).originx + (*(*SGPenManagement::activepenstroke).pointsx)[0] + offsetx, (*SGPenManagement::activepenstroke).originy +(*(*SGPenManagement::activepenstroke).pointsy)[0] + offsety, (*SGPenManagement::activepenstroke).originx +(*(*SGPenManagement::activepenstroke).pointsx)[0] - offsetx, (*SGPenManagement::activepenstroke).originy +(*(*SGPenManagement::activepenstroke).pointsy)[0] - offsety, (*SGPenManagement::activepenstroke).originx +(*(*SGPenManagement::activepenstroke).pointsx)[1] + offsetx, (*SGPenManagement::activepenstroke).originy +(*(*SGPenManagement::activepenstroke).pointsy)[1] + offsety, (*SGPenManagement::activepenstroke).originx +(*(*SGPenManagement::activepenstroke).pointsx)[1] - offsetx, (*SGPenManagement::activepenstroke).originy +(*(*SGPenManagement::activepenstroke).pointsy)[1] - offsety};
        GLuint newt[] = {0, 1, 2, 1, 2, 3};
        (*SGNoteViewManagement::penstrokerenderer).glBindVertexArray(SGPenManagement::vao);
        (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_ARRAY_BUFFER, SGPenManagement::vbo);
        (*SGNoteViewManagement::penstrokerenderer).glBufferSubData(GL_ARRAY_BUFFER, 0 * sizeof(GLfloat), 4 * 2 * sizeof(GLfloat), newv);
        SGPenManagement::vbors = 4;
        (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SGPenManagement::ebo);
        (*SGNoteViewManagement::penstrokerenderer).glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0 * sizeof(GLuint), 2 * 3 * sizeof(GLuint), newt);
        SGPenManagement::ebors = 2;
        (*SGNoteViewManagement::penstrokerenderer).update();
        (*SGNoteViewManagement::penstrokerenderer).doneCurrent();
    }
    else{
        (*SGNoteViewManagement::penstrokerenderer).makeCurrent();
        float a1x = (*(*SGPenManagement::activepenstroke).pointsx)[(*(*SGPenManagement::activepenstroke).pointsx).size()-3];
        float a1y = (*(*SGPenManagement::activepenstroke).pointsy)[(*(*SGPenManagement::activepenstroke).pointsy).size()-3];
        float a2x = (*(*SGPenManagement::activepenstroke).pointsx)[(*(*SGPenManagement::activepenstroke).pointsx).size()-2];
        float a2y = (*(*SGPenManagement::activepenstroke).pointsy)[(*(*SGPenManagement::activepenstroke).pointsy).size()-2];
        float a3x = (*(*SGPenManagement::activepenstroke).pointsx)[(*(*SGPenManagement::activepenstroke).pointsx).size()-1];
        float a3y = (*(*SGPenManagement::activepenstroke).pointsy)[(*(*SGPenManagement::activepenstroke).pointsy).size()-1];
        float offset1x;
        float offset1y;
        float offset2x;
        float offset2y;
        float offset3x;
        float offset3y;
        (*SGNoteViewManagement::penstrokerenderer).glBindVertexArray(SGPenManagement::vao);
        if(SGPenManagement::vboms <= SGPenManagement::vbors + 3){SGGeneralLibrary::doublevbo(SGNoteViewManagement::penstrokerenderer, SGPenManagement::vbo, SGPenManagement::vboms);}
        if(SGPenManagement::eboms <= SGPenManagement::ebors + 3){SGGeneralLibrary::doubleebo(SGNoteViewManagement::penstrokerenderer, SGPenManagement::ebo, SGPenManagement::eboms);}
        (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_ARRAY_BUFFER, SGPenManagement::vbo);
        (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SGPenManagement::ebo);
        (*SGNoteViewManagement::penstrokerenderer).glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(0 * sizeof(GLfloat)));
        (*SGNoteViewManagement::penstrokerenderer).glEnableVertexAttribArray(0);
        GLfloat newv[5 * 2];
        GLuint newt[] = {(GLuint)(SGPenManagement::vbors - 4), (GLuint)(SGPenManagement::vbors - 3), (GLuint)(SGPenManagement::vbors - 2), (GLuint)(SGPenManagement::vbors - 3), (GLuint)(SGPenManagement::vbors - 2), (GLuint)(SGPenManagement::vbors - 1), (GLuint)(SGPenManagement::vbors), (GLuint)(SGPenManagement::vbors - 1), (GLuint)(SGPenManagement::vbors - 2), (GLuint)(SGPenManagement::vbors + 1), (GLuint)(SGPenManagement::vbors), (GLuint)(SGPenManagement::vbors - 1), (GLuint)(SGPenManagement::vbors + 2), (GLuint)(SGPenManagement::vbors + 1), (GLuint)(SGPenManagement::vbors)};
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
        if((*(*SGPenManagement::activepenstroke).pointsx).size() > 3){
            float a0x = (*(*SGPenManagement::activepenstroke).pointsx)[(*(*SGPenManagement::activepenstroke).pointsx).size()-4];
            float a0y = (*(*SGPenManagement::activepenstroke).pointsy)[(*(*SGPenManagement::activepenstroke).pointsy).size()-4];
            float det0 = SGGeneralLibrary::getdetsignonly(a0x, a0y, a1x, a1y, a2x, a2y);
            if((det < 0 && det0 < 0) || (det >= 0 && det0 >= 0)){newt[2]++;}
        }
        perp2x = (0.5f) * (offset1x + offset3x);
        perp2y = (0.5f) * (offset1y + offset3y);
        SGGeneralLibrary::normalisevector(perp2x, perp2y, offset2x, offset2y);
        offset2x *= (0.05f * (*SGPenManagement::activepenstroke).width);
        offset2y *= (0.05f * (*SGPenManagement::activepenstroke).width);
        if(det < 0){
            newv[0] = a2x + offset1x + (*SGPenManagement::activepenstroke).originx;
            newv[1] = a2y + offset1y + (*SGPenManagement::activepenstroke).originy;
            newv[4] = a2x + offset3x + (*SGPenManagement::activepenstroke).originx;
            newv[5] = a2y + offset3y + (*SGPenManagement::activepenstroke).originy;
            newv[2] = a2x - offset2x + (*SGPenManagement::activepenstroke).originx;
            newv[3] = a2y - offset2y + (*SGPenManagement::activepenstroke).originy;
            newv[6] = a3x - offset3x + (*SGPenManagement::activepenstroke).originx;
            newv[7] = a3y - offset3y + (*SGPenManagement::activepenstroke).originy;
            newv[8] = a3x + offset3x + (*SGPenManagement::activepenstroke).originx;
            newv[9] = a3y + offset3y + (*SGPenManagement::activepenstroke).originy;
        }
        else{
            newv[0] = a2x - offset1x + (*SGPenManagement::activepenstroke).originx;
            newv[1] = a2y - offset1y + (*SGPenManagement::activepenstroke).originy;
            newv[4] = a2x - offset3x + (*SGPenManagement::activepenstroke).originx;
            newv[5] = a2y - offset3y + (*SGPenManagement::activepenstroke).originy;
            newv[2] = a2x + offset2x + (*SGPenManagement::activepenstroke).originx;
            newv[3] = a2y + offset2y + (*SGPenManagement::activepenstroke).originy;
            newv[6] = a3x + offset3x + (*SGPenManagement::activepenstroke).originx;
            newv[7] = a3y + offset3y + (*SGPenManagement::activepenstroke).originy;
            newv[8] = a3x - offset3x + (*SGPenManagement::activepenstroke).originx;
            newv[9] = a3y - offset3y + (*SGPenManagement::activepenstroke).originy;
        }
        (*SGNoteViewManagement::penstrokerenderer).glBindVertexArray(SGPenManagement::vao);
        (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_ARRAY_BUFFER, SGPenManagement::vbo);
        (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SGPenManagement::ebo);
        if(det >= 0 && (*(*SGPenManagement::activepenstroke).pointsx).size() == 3){
            GLfloat startv[] = {a1x - offset1x + (*SGPenManagement::activepenstroke).originx, a1y - offset1y + (*SGPenManagement::activepenstroke).originy, a1x + offset1x + (*SGPenManagement::activepenstroke).originx, a1y + offset1y + (*SGPenManagement::activepenstroke).originy};
            (*SGNoteViewManagement::penstrokerenderer).glBufferSubData(GL_ARRAY_BUFFER, 0 * sizeof(GLfloat), 2 * 2 * sizeof(GLfloat), startv);
        }
        (*SGNoteViewManagement::penstrokerenderer).glBufferSubData(GL_ARRAY_BUFFER, (SGPenManagement::vbors - 2) * 2 * sizeof(GLfloat), 5 * 2 * sizeof(GLfloat), newv);
        (*SGNoteViewManagement::penstrokerenderer).glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, (SGPenManagement::ebors - 2) * 3 * sizeof(GLuint), 5 * 3 * sizeof(GLuint), newt);
        SGPenManagement::vbors += 3;
        SGPenManagement::ebors += 3;
        (*SGNoteViewManagement::penstrokerenderer).update();
        (*SGNoteViewManagement::penstrokerenderer).doneCurrent();
    }
}

void SGPenManagement::endnewpenstroke(){
    (*SGNoteViewManagement::penstrokerenderer).makeCurrent();
    if(SGPenManagement::minp < 1){SGPenManagement::minp = 1;}
    if(SGPenManagement::maxp < 1){SGPenManagement::maxp = 1;}
    int pi = SGGeneralLibrary::getrenderingdataindex(SGPenManagement::minp, SGPenManagement::maxp);
    if((*SGNoteManagement::renderingdata).contains(pi) == false){(*SGNoteManagement::renderingdata)[pi] = new SGRenderingRange(SGPenManagement::minp, SGPenManagement::maxp);}
    unsigned long long k = (((unsigned long long)((uint)(*SGPenManagement::activepenstroke).zdepth)) << 32) | (uint)(*SGPenManagement::activepenstroke).colour;
    if((*(*(*SGNoteManagement::renderingdata)[pi]).penstrokelookuptable).contains(k) == false){
        (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokelookuptable)[k] = (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokezdepth).size();
        (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokezdepth).push_back((*SGPenManagement::activepenstroke).zdepth);
        (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokecolour).push_back((*SGPenManagement::activepenstroke).colour);
        GLuint vao0;
        (*SGNoteViewManagement::penstrokerenderer).glGenVertexArrays(1, &vao0);
        (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevao).push_back(vao0);
        (*SGNoteViewManagement::penstrokerenderer).glBindVertexArray(vao0);
        GLuint vbo0;
        (*SGNoteViewManagement::penstrokerenderer).glGenBuffers(1, &vbo0);
        (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevbo).push_back(vbo0);
        (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_ARRAY_BUFFER, vbo0);
        (*SGNoteViewManagement::penstrokerenderer).glBufferData(GL_ARRAY_BUFFER, 10 * 2 * sizeof(GLfloat), nullptr, GL_DYNAMIC_DRAW);
        GLfloat zerov[2] = {0.0f, 726.0f};
        (*SGNoteViewManagement::penstrokerenderer).glBufferSubData(GL_ARRAY_BUFFER, 0 * 2 * sizeof(GLfloat), 1 * 2 * sizeof(GLfloat), zerov);
        (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevbors).push_back(1);
        (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevboms).push_back(10);
        GLuint ebo0;
        (*SGNoteViewManagement::penstrokerenderer).glGenBuffers(1, &ebo0);
        (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokeebo).push_back(ebo0);
        (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo0);
        (*SGNoteViewManagement::penstrokerenderer).glBufferData(GL_ELEMENT_ARRAY_BUFFER, 10 * 3 * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
        (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokeebors).push_back(0);
        (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokeeboms).push_back(10);
    }
    int di = (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokelookuptable)[k];
    while((*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevboms)[di] <= (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevbors)[di] + SGPenManagement::vbors){SGGeneralLibrary::doublevbo(SGNoteViewManagement::penstrokerenderer, (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevbo)[di], (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevboms)[di]);}
    while((*(*(*SGNoteManagement::renderingdata)[pi]).penstrokeeboms)[di] <= (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokeebors)[di] + SGPenManagement::ebors){SGGeneralLibrary::doubleebo(SGNoteViewManagement::penstrokerenderer, (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokeebo)[di], (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokeeboms)[di]);}

    GLuint vao1;
    (*SGNoteViewManagement::penstrokerenderer).glGenVertexArrays(1, &vao1);
    (*SGNoteViewManagement::penstrokerenderer).glBindVertexArray(vao1);
    GLuint ebo1;
    (*SGNoteViewManagement::penstrokerenderer).glGenBuffers(1, &ebo1);
    (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_ARRAY_BUFFER, ebo1);
    (*SGNoteViewManagement::penstrokerenderer).glBufferData(GL_ARRAY_BUFFER, SGPenManagement::ebors * 3 * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
    (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_ARRAY_BUFFER, SGPenManagement::ebo);
    (*SGNoteViewManagement::penstrokerenderer).glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(GLuint), (void*)(0 * sizeof(GLuint)));
    (*SGNoteViewManagement::penstrokerenderer).glEnableVertexAttribArray(0);
    (*SGNoteViewManagement::penstrokerenderer).glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, ebo1);
    (*(*SGNoteViewManagement::penstrokerenderer).transformfeedbackshaderprogramme).bind();
    (*SGNoteViewManagement::penstrokerenderer).glUniform1ui((*SGNoteViewManagement::penstrokerenderer).gvptransformfeedbackoffset, (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevbors)[di]);
    (*SGNoteViewManagement::penstrokerenderer).glEnable(GL_RASTERIZER_DISCARD);
    (*SGNoteViewManagement::penstrokerenderer).glBeginTransformFeedback(GL_POINTS);
    (*SGNoteViewManagement::penstrokerenderer).glDrawArrays(GL_POINTS, 0, SGPenManagement::ebors * 3);
    (*SGNoteViewManagement::penstrokerenderer).glEndTransformFeedback();
    (*SGNoteViewManagement::penstrokerenderer).glDisable(GL_RASTERIZER_DISCARD);

    (*SGPenManagement::activepenstroke).renderrangeindex = pi;
    (*SGPenManagement::activepenstroke).renderkey = di;
    (*SGNoteViewManagement::penstrokerenderer).glBindVertexArray((*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevao)[di]);
    (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_ARRAY_BUFFER, (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevbo)[di]);
    (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokeebo)[di]);
    (*SGNoteViewManagement::penstrokerenderer).glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(0 * sizeof(GLfloat)));
    (*SGNoteViewManagement::penstrokerenderer).glEnableVertexAttribArray(0);
    (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_COPY_READ_BUFFER, SGPenManagement::vbo);
    (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_COPY_WRITE_BUFFER, (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevbo)[di]);
    (*SGNoteViewManagement::penstrokerenderer).glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0 * sizeof(GLfloat), (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevbors)[di] * 2 * sizeof(GLfloat), SGPenManagement::vbors * 2 * sizeof(GLfloat));
    (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokevbors)[di] += SGPenManagement::vbors;
    (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_COPY_READ_BUFFER, ebo1);
    (*SGNoteViewManagement::penstrokerenderer).glBindBuffer(GL_COPY_WRITE_BUFFER, (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokeebo)[di]);
    (*SGNoteViewManagement::penstrokerenderer).glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0 * 3 * sizeof(GLuint), (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokeebors)[di] * 3 * sizeof(GLuint), SGPenManagement::ebors * 3 * sizeof(GLuint));
    (*SGPenManagement::activepenstroke).ebostartindex = (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokeebors)[di];
    (*SGPenManagement::activepenstroke).ebolength = SGPenManagement::ebors;
    (*SGNoteViewManagement::penstrokerenderer).glDeleteBuffers(1, &ebo1);
    (*(*(*SGNoteManagement::renderingdata)[pi]).penstrokeebors)[di] += SGPenManagement::ebors;
    (*SGNoteViewManagement::penstrokerenderer).glDeleteVertexArrays(1, &SGPenManagement::vao);
    (*SGNoteViewManagement::penstrokerenderer).glDeleteBuffers(1, &SGPenManagement::vbo);
    (*SGNoteViewManagement::penstrokerenderer).glDeleteBuffers(1, &SGPenManagement::ebo);
    SGPenManagement::vbors = 0;
    SGPenManagement::vboms = 0;
    SGPenManagement::ebors = 0;
    SGPenManagement::eboms = 0;
    SGPenManagement::minp = 0;
    SGPenManagement::maxp = 0;
    (*SGPenManagement::activepenstroke).dataindex = (*SGNoteManagement::notedata).size();
    (*SGNoteManagement::notedata).push_back(SGPenManagement::activepenstroke);
    (*SGNoteViewManagement::penstrokerenderer).update();
    (*SGNoteViewManagement::penstrokerenderer).doneCurrent();
    int rangeidx;
    int idx;
    SGPolylineCollider* col = SGColliderManagement::penstrokegetcollider(SGPenManagement::activepenstroke);
    SGColliderManagement::registercollider(col, SGNoteObjectTypeEnum::PenStroke, rangeidx, idx);
    (*SGPenManagement::activepenstroke).colliderrangeindex = rangeidx;
    (*SGPenManagement::activepenstroke).colliderindex = idx;
    SGPenManagement::activepenstroke = nullptr;
}
