#ifndef SGNOTEPENSTROKERENDERER_H
#define SGNOTEPENSTROKERENDERER_H

#include <QWidget>
#include "openglincludes.h"

class SGNotePenStrokeRenderer : public QOpenGLWidget, public QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    SGNotePenStrokeRenderer(QWidget *parent);
    ~SGNotePenStrokeRenderer();
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    QOpenGLShaderProgram* shaderprogramme;
    QOpenGLShader* vertexshader;
    QOpenGLShader* fragmentshader;
    GLuint gvpviewportdata;
    GLuint gvpwindowsize;
    GLuint gvpincolour;
    GLuint gvpzdepth;
    void renderpagerange(int n);
    QOpenGLShader* transformfeedbackvertexshader;
    QOpenGLShaderProgram* transformfeedbackshaderprogramme;
    GLuint gvptransformfeedbackoffset;

public slots:
    void ResizeObj();
};

#endif // SGNOTEPENSTROKERENDERER_H
