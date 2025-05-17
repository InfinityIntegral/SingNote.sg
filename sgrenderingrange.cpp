#include "sgrenderingrange.h"
#include "sgnoteviewmanagement.h"

SGRenderingRange::SGRenderingRange(int a, int b){
    (*this).startpage = a;
    (*this).endpage = b;
    (*this).penstrokelookuptable = new QHash<unsigned long long, int>();
    (*this).highlighterstrokelookuptable = new QHash<unsigned long long, int>();
    (*this).pagebackgroundvao = 0;
    (*this).pagebackgroundvbo = 0;
    (*this).pagebackgroundebo = 0;
    (*this).penstrokezdepth = new QVector<int>();
    (*this).penstrokecolour = new QVector<uint>();
    (*this).penstrokevao = new QVector<GLuint>();
    (*this).penstrokevbo = new QVector<GLuint>();
    (*this).penstrokevbors = new QVector<int>();
    (*this).penstrokevboms = new QVector<int>();
    (*this).penstrokeebo = new QVector<GLuint>();
    (*this).penstrokeebors = new QVector<int>();
    (*this).penstrokeeboms = new QVector<int>();
    (*this).highlighterstrokezdepth = new QVector<int>();
    (*this).highlighterstrokecolour = new QVector<uint>();
    (*this).highlighterstrokevao = new QVector<GLuint>();
    (*this).highlighterstrokevbo = new QVector<GLuint>();
    (*this).highlighterstrokevbors = new QVector<int>();
    (*this).highlighterstrokevboms = new QVector<int>();
    (*this).highlighterstrokeebo = new QVector<GLuint>();
    (*this).highlighterstrokeebors = new QVector<int>();
    (*this).highlighterstrokeeboms = new QVector<int>();
}

SGRenderingRange::~SGRenderingRange(){
    delete (*this).penstrokelookuptable;
    delete (*this).highlighterstrokelookuptable;
    delete (*this).penstrokezdepth;
    delete (*this).penstrokecolour;
    for(int i=0; i<(*(*this).penstrokevao).size(); i++){(*SGNoteViewManagement::penstrokerenderer).glDeleteVertexArrays(1, &(*(*this).penstrokevao)[i]);}
    delete (*this).penstrokevao;
    for(int i=0; i<(*(*this).penstrokevbo).size(); i++){(*SGNoteViewManagement::penstrokerenderer).glDeleteBuffers(1, &(*(*this).penstrokevbo)[i]);}
    delete (*this).penstrokevbo;
    delete (*this).penstrokevbors;
    delete (*this).penstrokevboms;
    for(int i=0; i<(*(*this).penstrokeebo).size(); i++){(*SGNoteViewManagement::penstrokerenderer).glDeleteBuffers(1, &(*(*this).penstrokeebo)[i]);}
    delete (*this).penstrokeebo;
    delete (*this).penstrokeebors;
    delete (*this).penstrokeeboms;
    delete (*this).highlighterstrokezdepth;
    delete (*this).highlighterstrokecolour;
    for(int i=0; i<(*(*this).highlighterstrokevao).size(); i++){(*SGNoteViewManagement::highlighterstrokerenderer).glDeleteVertexArrays(1, &(*(*this).highlighterstrokevao)[i]);}
    delete (*this).highlighterstrokevao;
    for(int i=0; i<(*(*this).highlighterstrokevbo).size(); i++){(*SGNoteViewManagement::highlighterstrokerenderer).glDeleteBuffers(1, &(*(*this).highlighterstrokevbo)[i]);}
    delete (*this).highlighterstrokevbo;
    delete (*this).highlighterstrokevbors;
    delete (*this).highlighterstrokevboms;
    for(int i=0; i<(*(*this).highlighterstrokeebo).size(); i++){(*SGNoteViewManagement::highlighterstrokerenderer).glDeleteBuffers(1, &(*(*this).highlighterstrokeebo)[i]);}
    delete (*this).highlighterstrokeebo;
    delete (*this).highlighterstrokeebors;
    delete (*this).highlighterstrokeeboms;
}
