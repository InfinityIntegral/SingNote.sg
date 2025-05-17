#include "sgnoteuirenderer.h"
#include "sgnotemanagement.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"
#include "sgerasermanagement.h"
#include "sgpenstrokeselectormanagement.h"
#include "sgicon022111132.h"

SGNoteUIRenderer::SGNoteUIRenderer(QWidget *parent){
    (*this).setParent(parent);
    (*this).show();
    (*this).ResizeObj();
}

SGNoteUIRenderer::~SGNoteUIRenderer(){
    makeCurrent();
    doneCurrent();
}

void SGNoteUIRenderer::initializeGL(){
    initializeOpenGLFunctions();
    setAttribute(Qt::WA_AlwaysStackOnTop);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    vertexshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    (*vertexshader).compileSourceFile(":/assets/noteui.vert");
    fragmentshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    (*fragmentshader).compileSourceFile(":/assets/noteui.frag");
    shaderprogramme = new QOpenGLShaderProgram(this);
    (*shaderprogramme).addShader(vertexshader);
    (*shaderprogramme).addShader(fragmentshader);
    (*shaderprogramme).link();
    gvpviewportdata = (*shaderprogramme).uniformLocation("viewportdata");
    gvpwindowsize = (*shaderprogramme).uniformLocation("windowsize");
    gvpincolour = (*shaderprogramme).uniformLocation("incolour");
    gvpposcenter = (*shaderprogramme).uniformLocation("poscenter");
    gvprendertype = (*shaderprogramme).uniformLocation("rendertype");
    gvpselectortopleft = (*shaderprogramme).uniformLocation("selectortopleft");
    gvpselectorsize = (*shaderprogramme).uniformLocation("selectorsize");
    gvpcolour1 = (*shaderprogramme).uniformLocation("colour1");
    gvpcolour2 = (*shaderprogramme).uniformLocation("colour2");
    gvpicontexture = (*shaderprogramme).uniformLocation("icontexture");
    gvpsizeunit = (*shaderprogramme).uniformLocation("sizeunit");

    SGIcon022111132 *r = new SGIcon022111132(this, "", 0.0f, 0.0f, 1.5f, 1.5f);
    QString white = "rgba(255, 255, 255, 255)";
    QString black = "rgba(0, 0, 0, 0)";
    SGGeneralLibrary::SetUIStyle(r, SGGeneralLibrary::stylesheetfieldtextcolour, white);
    SGGeneralLibrary::SetUIStyle(r, SGGeneralLibrary::stylesheetfieldbackgroundcolour, black);
    (*r).setText("\uE024");
    glGenTextures(1, &selecticon);
    glBindTexture(GL_TEXTURE_2D, selecticon);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    uchar* img = (*r).grab().toImage().convertToFormat(QImage::Format_RGBA8888).bits();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (*r).size().width(), (*r).size().height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    delete r;
}

void SGNoteUIRenderer::paintGL(){
    if(SGNoteManagement::noteisopen == false){return;}
    glClear(GL_COLOR_BUFFER_BIT);
    (*shaderprogramme).bind();
    glUniform3f(gvpviewportdata, SGCentralManagement::focusedpositionx, SGCentralManagement::focusedpositiony, SGCentralManagement::focusedzoom);
    glUniform2f(gvpwindowsize, (*this).size().width(), (*this).size().height());
    glUniform1ui(gvpincolour, (SGGeneralLibrary::ColourCSSToUint(SGCentralManagement::colour1) & (uint)0xFFFFFF00) | (uint)0x00000080);
    if(SGEraserManagement::vao != 0){
        glUniform1i(gvprendertype, 0);
        glUniform2f(gvpposcenter, SGEraserManagement::posx, SGEraserManagement::posy);
        glBindVertexArray(SGEraserManagement::vao);
        glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, (void*)(0 * sizeof(GLuint)));
    }
    else if(SGPenStrokeSelectorManagement::vao != 0){
        glUniform1i(gvprendertype, 1);
        glUniform2f(gvpselectortopleft, SGPenStrokeSelectorManagement::selectorx, SGPenStrokeSelectorManagement::selectory);
        glUniform2f(gvpselectorsize, SGPenStrokeSelectorManagement::selectorw, SGPenStrokeSelectorManagement::selectorh);
        glBindVertexArray(SGPenStrokeSelectorManagement::vao);
        glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, (void*)(0 * sizeof(GLuint)));
        if(SGPenStrokeSelectorManagement::resizevao != 0){
            glUniform1i(gvprendertype, 2);
            glUniform1i(gvpicontexture, 0);
            glUniform1f(gvpsizeunit, SGCentralManagement::sizeunit);
            glUniform1ui(gvpcolour1, SGGeneralLibrary::ColourCSSToUint(SGCentralManagement::colour1));
            glUniform1ui(gvpcolour2, SGGeneralLibrary::ColourCSSToUint(SGCentralManagement::colour2));
            glBindTexture(GL_TEXTURE_2D, selecticon);
            glBindVertexArray(SGPenStrokeSelectorManagement::resizevao);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0 * sizeof(GLuint)));
        }
    }
}

void SGNoteUIRenderer::resizeGL(int w, int h){
    glViewport(0, 0, w, h);
}

void SGNoteUIRenderer::ResizeObj(){
    (*this).resize((*parentWidget()).size());
}
