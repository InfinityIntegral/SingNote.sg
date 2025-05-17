#ifndef SGNOTEQUICKMOVERENDERER_H
#define SGNOTEQUICKMOVERENDERER_H

#include <QWidget>
#include "openglincludes.h"

class SGNoteQuickMoveRenderer : public QOpenGLWidget, public QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    SGNoteQuickMoveRenderer(QWidget* parent);
    ~SGNoteQuickMoveRenderer();
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    QOpenGLShaderProgram* shaderprogramme;
    QOpenGLShader* vertexshader;
    QOpenGLShader* fragmentshader;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLuint gvpquickmovepos;
    GLuint gvpiconpos;
    GLuint gvpwindowsize;
    GLuint gvpicontexture;
    GLuint gvpcolour1;
    GLuint gvpcolour2;
    QOpenGLTexture* maintexture;
    void uploadtextures();
    GLuint mainicon;
    GLuint upicon;
    GLuint downicon;
    GLuint lefticon;
    GLuint righticon;
    GLuint inicon;
    GLuint outicon;

public slots:
    void ResizeObj();
};

#endif // SGNOTEQUICKMOVERENDERER_H
