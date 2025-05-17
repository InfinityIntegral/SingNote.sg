#ifndef SGNOTEBACKGROUNDRENDERER_H
#define SGNOTEBACKGROUNDRENDERER_H

#include <QWidget>
#include "openglincludes.h"

class SGNoteBackgroundRenderer : public QOpenGLWidget, public QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    SGNoteBackgroundRenderer(QWidget *parent);
    ~SGNoteBackgroundRenderer();
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void renderpage(int n);
    QOpenGLShaderProgram* shaderprogramme;
    QOpenGLShader* vertexshader;
    QOpenGLShader* fragmentshader;
    GLuint gvpviewportdata;
    GLuint gvpwindowsize;

public slots:
    void ResizeObj();
};

#endif // SGNOTEBACKGROUNDRENDERER_H
