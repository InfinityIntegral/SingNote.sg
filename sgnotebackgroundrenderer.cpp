#include "sgnotebackgroundrenderer.h"
#include "sgcentralmanagement.h"
#include "sgnotemanagement.h"
#include "sgnoteviewmanagement.h"
#include "sggenerallibrary.h"

SGNoteBackgroundRenderer::SGNoteBackgroundRenderer(QWidget *parent){
    (*this).setParent(parent);
    (*this).show();
    (*this).ResizeObj();
}

SGNoteBackgroundRenderer::~SGNoteBackgroundRenderer(){
    makeCurrent();
    doneCurrent();
}

void SGNoteBackgroundRenderer::initializeGL(){
    initializeOpenGLFunctions();
    setAttribute(Qt::WA_AlwaysStackOnTop);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    vertexshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    (*vertexshader).compileSourceFile(":/assets/notebackground.vert");
    fragmentshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    (*fragmentshader).compileSourceFile(":/assets/notebackground.frag");
    shaderprogramme = new QOpenGLShaderProgram(this);
    (*shaderprogramme).addShader(vertexshader);
    (*shaderprogramme).addShader(fragmentshader);
    (*shaderprogramme).link();
    gvpviewportdata = (*shaderprogramme).uniformLocation("viewportdata");
    gvpwindowsize = (*shaderprogramme).uniformLocation("windowsize");
}

void SGNoteBackgroundRenderer::resizeGL(int w, int h){
    glViewport(0, 0, w, h);
}

void SGNoteBackgroundRenderer::paintGL(){
    if(SGNoteManagement::noteisopen == false){return;}
    (*shaderprogramme).bind();
    glClear(GL_COLOR_BUFFER_BIT);
    glUniform3f(gvpviewportdata, SGCentralManagement::focusedpositionx, SGCentralManagement::focusedpositiony, SGCentralManagement::focusedzoom);
    glUniform2f(gvpwindowsize, (*this).size().width(), (*this).size().height());
    int a = 1 + std::floor((-0.5f * SGCentralManagement::focusedzoom / (*this).size().width() * (*this).size().height() - SGCentralManagement::focusedpositiony) / SGCentralManagement::pageh);
    if(a<1){a = 1;}
    int b = std::ceil((0.5f * SGCentralManagement::focusedzoom / (*this).size().width() * (*this).size().height() - SGCentralManagement::focusedpositiony) / SGCentralManagement::pageh);
    if(b<1){b = 1;}
    for(int i=a; i<=b; i++){
        if((*SGNoteManagement::renderingdata).contains(SGGeneralLibrary::getrenderingdataindex(i, i)) && (*(*SGNoteManagement::renderingdata)[SGGeneralLibrary::getrenderingdataindex(i, i)]).pagebackgroundvao != 0){renderpage(SGGeneralLibrary::getrenderingdataindex(i, i));}
    }
}

void SGNoteBackgroundRenderer::ResizeObj(){
    (*this).resize((*parentWidget()).size());
    SGNoteViewManagement::renderw = (*this).size().width();
    SGNoteViewManagement::renderh = (*this).size().height();
}

void SGNoteBackgroundRenderer::renderpage(int n){
    glBindVertexArray((*(*SGNoteManagement::renderingdata)[n]).pagebackgroundvao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0 * sizeof(GLuint)));
}
