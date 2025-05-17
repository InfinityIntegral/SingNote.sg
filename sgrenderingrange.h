#ifndef SGRENDERINGRANGE_H
#define SGRENDERINGRANGE_H

#include "sgnoteobject.h"
#include "openglincludes.h"
#include "sgpagebackgroundobject.h"

class SGRenderingRange : public SGNoteObject
{
public:
    SGRenderingRange(int a, int b);
    ~SGRenderingRange();
    int startpage;
    int endpage;
    QHash<unsigned long long, int>* penstrokelookuptable;
    QHash<unsigned long long, int>* highlighterstrokelookuptable;
    GLuint pagebackgroundvao;
    GLuint pagebackgroundvbo;
    GLuint pagebackgroundebo;
    QVector<int>* penstrokezdepth;
    QVector<uint>* penstrokecolour;
    QVector<GLuint>* penstrokevao;
    QVector<GLuint>* penstrokevbo;
    QVector<int>* penstrokevbors;
    QVector<int>* penstrokevboms;
    QVector<GLuint>* penstrokeebo;
    QVector<int>* penstrokeebors;
    QVector<int>* penstrokeeboms;
    QVector<int>* highlighterstrokezdepth;
    QVector<uint>* highlighterstrokecolour;
    QVector<GLuint>* highlighterstrokevao;
    QVector<GLuint>* highlighterstrokevbo;
    QVector<int>* highlighterstrokevbors;
    QVector<int>* highlighterstrokevboms;
    QVector<GLuint>* highlighterstrokeebo;
    QVector<int>* highlighterstrokeebors;
    QVector<int>* highlighterstrokeeboms;
};

#endif // SGRENDERINGRANGE_H
