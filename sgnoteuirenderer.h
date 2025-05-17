#ifndef SGNOTEUIRENDERER_H
#define SGNOTEUIRENDERER_H

#include <QWidget>
#include "openglincludes.h"

class SGNoteUIRenderer : public QOpenGLWidget, public QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    SGNoteUIRenderer(QWidget *parent);
    ~SGNoteUIRenderer();
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    QOpenGLShaderProgram* shaderprogramme;
    QOpenGLShader* vertexshader;
    QOpenGLShader* fragmentshader;
    GLuint gvpviewportdata;
    GLuint gvpwindowsize;
    GLuint gvpincolour;
    GLuint gvpposcenter;
    GLuint gvprendertype;
    GLuint gvpselectortopleft;
    GLuint gvpselectorsize;
    GLuint selecticon;
    GLuint gvpcolour1;
    GLuint gvpcolour2;
    GLuint gvpicontexture;
    GLuint gvpsizeunit;

public slots:
    void ResizeObj();
};

#endif // SGNOTEUIRENDERER_H
