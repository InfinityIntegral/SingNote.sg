#include "sgnotequickmoverenderer.h"
#include "sgnoteviewmanagement.h"
#include "sgcentralmanagement.h"
#include "sgicon022111132.h"
#include "sgtouchinputmanagement.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"

SGNoteQuickMoveRenderer::SGNoteQuickMoveRenderer(QWidget *parent){
    (*this).setParent(parent);
    (*this).show();
    (*this).ResizeObj();
}

SGNoteQuickMoveRenderer::~SGNoteQuickMoveRenderer(){
    makeCurrent();
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteTextures(1, &mainicon);
    glDeleteTextures(1, &upicon);
    glDeleteTextures(1, &downicon);
    glDeleteTextures(1, &lefticon);
    glDeleteTextures(1, &righticon);
    glDeleteTextures(1, &inicon);
    glDeleteTextures(1, &outicon);
    doneCurrent();
}

void SGNoteQuickMoveRenderer::ResizeObj(){
    (*this).move(QPoint(0.0f, 0.0f));
    (*this).resize((*parentWidget()).size());
}

void SGNoteQuickMoveRenderer::initializeGL(){
    initializeOpenGLFunctions();
    setAttribute(Qt::WA_AlwaysStackOnTop);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    vertexshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    (*vertexshader).compileSourceFile(":/assets/notequickmove.vert");
    fragmentshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    (*fragmentshader).compileSourceFile(":/assets/notequickmove.frag");
    shaderprogramme = new QOpenGLShaderProgram(this);
    (*shaderprogramme).addShader(vertexshader);
    (*shaderprogramme).addShader(fragmentshader);
    (*shaderprogramme).link();
    gvpquickmovepos = (*shaderprogramme).uniformLocation("quickmovepos");
    gvpiconpos = (*shaderprogramme).uniformLocation("iconpos");
    gvpwindowsize = (*shaderprogramme).uniformLocation("windowsize");
    gvpicontexture = (*shaderprogramme).uniformLocation("icontexture");
    gvpcolour1 = (*shaderprogramme).uniformLocation("colour1");
    gvpcolour2 = (*shaderprogramme).uniformLocation("colour2");

    GLfloat vts[] = {0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f};
    GLuint ids[] = {0, 1, 2, 1, 2, 3};
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(GLfloat), vts, GL_DYNAMIC_DRAW);
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * 3 * sizeof(GLuint), ids, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);

    uploadtextures();
}

void SGNoteQuickMoveRenderer::paintGL(){
    (*shaderprogramme).bind();
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(vao);
    glUniform2f(gvpquickmovepos, SGTouchInputManagement::quickmovex, SGTouchInputManagement::quickmovey);
    glUniform2f(gvpwindowsize, (*SGNoteViewManagement::renderarea).size().width() / SGCentralManagement::sizeunit, (*SGNoteViewManagement::renderarea).size().height() / SGCentralManagement::sizeunit);
    glUniform1i(gvpicontexture, 0);
    glUniform1ui(gvpcolour1, SGGeneralLibrary::ColourCSSToUint(SGCentralManagement::colour1));
    glUniform1ui(gvpcolour2, SGGeneralLibrary::ColourCSSToUint(SGCentralManagement::colour2));
    glBindTexture(GL_TEXTURE_2D, mainicon);
    glUniform2f(gvpiconpos, 0.0f, 0.0f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0 * sizeof(GLuint)));
    if(SGNoteViewManagement::quickmoveenabled){
        glBindTexture(GL_TEXTURE_2D, upicon);
        glUniform2f(gvpiconpos, 0.0f, -1.5f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0 * sizeof(GLuint)));
        glBindTexture(GL_TEXTURE_2D, downicon);
        glUniform2f(gvpiconpos, 0.0f, 1.5f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0 * sizeof(GLuint)));
        glBindTexture(GL_TEXTURE_2D, lefticon);
        glUniform2f(gvpiconpos, -1.5f, 0.0f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0 * sizeof(GLuint)));
        glBindTexture(GL_TEXTURE_2D, righticon);
        glUniform2f(gvpiconpos, 1.5f, 0.0f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0 * sizeof(GLuint)));
        glBindTexture(GL_TEXTURE_2D, inicon);
        glUniform2f(gvpiconpos, -0.75f, 3.0f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0 * sizeof(GLuint)));
        glBindTexture(GL_TEXTURE_2D, outicon);
        glUniform2f(gvpiconpos, 0.75f, 3.0f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0 * sizeof(GLuint)));
    }
}

void SGNoteQuickMoveRenderer::resizeGL(int w, int h){
    glViewport(0, 0, w, h);
}

void SGNoteQuickMoveRenderer::uploadtextures(){
    SGIcon022111132 *r = new SGIcon022111132(this, "", 0.0f, 0.0f, 1.5f, 1.5f);
    QString white = "rgba(255, 255, 255, 255)";
    QString black = "rgba(0, 0, 0, 0)";
    SGGeneralLibrary::SetUIStyle(r, SGGeneralLibrary::stylesheetfieldtextcolour, white);
    SGGeneralLibrary::SetUIStyle(r, SGGeneralLibrary::stylesheetfieldbackgroundcolour, black);
    (*r).setText("\uE015");
    glGenTextures(1, &mainicon);
    glBindTexture(GL_TEXTURE_2D, mainicon);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    uchar* img = (*r).grab().toImage().convertToFormat(QImage::Format_RGBA8888).bits();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (*r).size().width(), (*r).size().height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    (*r).setText("\uE016");
    glGenTextures(1, &upicon);
    glBindTexture(GL_TEXTURE_2D, upicon);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    img = (*r).grab().toImage().convertToFormat(QImage::Format_RGBA8888).bits();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (*r).size().width(), (*r).size().height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    (*r).setText("\uE017");
    glGenTextures(1, &downicon);
    glBindTexture(GL_TEXTURE_2D, downicon);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    img = (*r).grab().toImage().convertToFormat(QImage::Format_RGBA8888).bits();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (*r).size().width(), (*r).size().height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    (*r).setText("\uE018");
    glGenTextures(1, &lefticon);
    glBindTexture(GL_TEXTURE_2D, lefticon);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    img = (*r).grab().toImage().convertToFormat(QImage::Format_RGBA8888).bits();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (*r).size().width(), (*r).size().height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    (*r).setText("\uE019");
    glGenTextures(1, &righticon);
    glBindTexture(GL_TEXTURE_2D, righticon);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    img = (*r).grab().toImage().convertToFormat(QImage::Format_RGBA8888).bits();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (*r).size().width(), (*r).size().height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    (*r).setText("\uE01A");
    glGenTextures(1, &inicon);
    glBindTexture(GL_TEXTURE_2D, inicon);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    img = (*r).grab().toImage().convertToFormat(QImage::Format_RGBA8888).bits();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (*r).size().width(), (*r).size().height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    (*r).setText("\uE01B");
    glGenTextures(1, &outicon);
    glBindTexture(GL_TEXTURE_2D, outicon);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    img = (*r).grab().toImage().convertToFormat(QImage::Format_RGBA8888).bits();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (*r).size().width(), (*r).size().height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    delete r;
}
