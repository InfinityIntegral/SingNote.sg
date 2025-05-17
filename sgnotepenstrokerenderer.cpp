#include "sgnotepenstrokerenderer.h"
#include "sgcentralmanagement.h"
#include "sgpenmanagement.h"
#include "sgnotemanagement.h"

SGNotePenStrokeRenderer::SGNotePenStrokeRenderer(QWidget *parent){
    (*this).setParent(parent);
    (*this).show();
    (*this).ResizeObj();
}

SGNotePenStrokeRenderer::~SGNotePenStrokeRenderer(){
    makeCurrent();
    doneCurrent();
}

void SGNotePenStrokeRenderer::initializeGL(){
    initializeOpenGLFunctions();
    setAttribute(Qt::WA_AlwaysStackOnTop);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);

    vertexshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    (*vertexshader).compileSourceFile(":/assets/notepenstroke.vert");
    fragmentshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    (*fragmentshader).compileSourceFile(":/assets/notepenstroke.frag");
    shaderprogramme = new QOpenGLShaderProgram(this);
    (*shaderprogramme).addShader(vertexshader);
    (*shaderprogramme).addShader(fragmentshader);
    (*shaderprogramme).link();
    gvpviewportdata = (*shaderprogramme).uniformLocation("viewportdata");
    gvpwindowsize = (*shaderprogramme).uniformLocation("windowsize");
    gvpincolour = (*shaderprogramme).uniformLocation("incolour");
    gvpzdepth = (*shaderprogramme).uniformLocation("zdepth");

    transformfeedbackvertexshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    (*transformfeedbackvertexshader).compileSourceFile(":/assets/notepenstrokeoffset.vert");
    transformfeedbackshaderprogramme = new QOpenGLShaderProgram(this);
    const char* outv[] = {"outv"};
    (*transformfeedbackshaderprogramme).addShader(transformfeedbackvertexshader);
    glTransformFeedbackVaryings((*transformfeedbackshaderprogramme).programId(), 1, outv, GL_INTERLEAVED_ATTRIBS);
    (*transformfeedbackshaderprogramme).link();
    gvptransformfeedbackoffset = (*transformfeedbackshaderprogramme).uniformLocation("ofs");
}

void SGNotePenStrokeRenderer::resizeGL(int w, int h){
    glViewport(0, 0, w, h);
}

void SGNotePenStrokeRenderer::paintGL(){
    if(SGNoteManagement::noteisopen == false){return;}
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    (*shaderprogramme).bind();
    glUniform3f(gvpviewportdata, SGCentralManagement::focusedpositionx, SGCentralManagement::focusedpositiony, SGCentralManagement::focusedzoom);
    glUniform2f(gvpwindowsize, (*this).size().width(), (*this).size().height());
    if(SGPenManagement::activepenstroke != nullptr){
        glUniform1ui(gvpincolour, (*SGPenManagement::activepenstroke).colour);
        glUniform1i(gvpzdepth, (*SGPenManagement::activepenstroke).zdepth);
        glBindVertexArray(SGPenManagement::vao);
        glDrawElements(GL_TRIANGLES, 3 * SGPenManagement::ebors, GL_UNSIGNED_INT, (void*)(0 * sizeof(GLuint)));
    }
    int a = 1 + std::floor((-0.5f * SGCentralManagement::focusedzoom / (*this).size().width() * (*this).size().height() - SGCentralManagement::focusedpositiony) / SGCentralManagement::pageh);
    if(a<1){a = 1;}
    int b = std::ceil((0.5f * SGCentralManagement::focusedzoom / (*this).size().width() * (*this).size().height() - SGCentralManagement::focusedpositiony) / SGCentralManagement::pageh);
    if(b<1){b = 1;}
    for(QHash<int, SGRenderingRange*>::iterator i = (*SGNoteManagement::renderingdata).begin(); i != (*SGNoteManagement::renderingdata).end(); i++){
        if((*i.value()).startpage <= b && (*i.value()).endpage >= a){renderpagerange(i.key());}
    }
}

void SGNotePenStrokeRenderer::ResizeObj(){
    (*this).resize((*parentWidget()).size());
}

void SGNotePenStrokeRenderer::renderpagerange(int n){
    for(int i=0; i<(*(*(*SGNoteManagement::renderingdata)[n]).penstrokezdepth).size(); i++){
        glUniform1i(gvpzdepth, (*(*(*SGNoteManagement::renderingdata)[n]).penstrokezdepth)[i]);
        glUniform1ui(gvpincolour, (*(*(*SGNoteManagement::renderingdata)[n]).penstrokecolour)[i]);
        glBindVertexArray((*(*(*SGNoteManagement::renderingdata)[n]).penstrokevao)[i]);
        glDrawElements(GL_TRIANGLES, 3 * (*(*(*SGNoteManagement::renderingdata)[n]).penstrokeebors)[i], GL_UNSIGNED_INT, (void*)(0 * sizeof(GLuint)));
    }
}
