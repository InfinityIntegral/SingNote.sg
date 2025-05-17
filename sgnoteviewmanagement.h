#ifndef SGNOTEVIEWMANAGEMENT_H
#define SGNOTEVIEWMANAGEMENT_H

#include <QObject>
#include "sgwidget000221103.h"
#include "sgwidget000211103.h"
#include "sgwidget000331104.h"
#include "sgnotebackgroundrenderer.h"
#include "sglayoutnotetoolbar.h"
#include "sgnoteviewtouchprocessor.h"
#include "sgnotequickmoverenderer.h"
#include "sgnotepenstrokerenderer.h"
#include "sgtext012211121.h"
#include "sgnoteuirenderer.h"
#include "sgnotehighlighterstrokerenderer.h"
#include "sgfavouritetoolbutton.h"
#include "sgwidget000133103.h"
#include "sgscrollview000231100.h"
#include "sglayoutfavouritetools.h"
#include "sgiconbutton022111132.h"

class SGNoteViewManagement : public QObject
{
    Q_OBJECT
public:
    static void initialisenoteview();
    static float renderw;
    static float renderh;
    static SGWidget000221103* noteviewbackground;
    static SGWidget000331104* renderarea;
    static SGWidget000211103* toolbarbackground;
    static SGLayoutNoteToolbar* toolbarlayout;
    static SGNoteBackgroundRenderer* backgroundrenderer;
    static void exitnote();
    static SGIconButton022110032* exitnotebutton;
    static SGNoteViewTouchProcessor* touchprocessor;
    static void updaterendering();
    static SGNoteQuickMoveRenderer* quickmoverenderer;
    static bool quickmoveenabled;
    static SGFavouriteToolButton* changetoolbutton;
    static SGNotePenStrokeRenderer* penstrokerenderer;
    static SGNoteUIRenderer* uirenderer;
    static SGNoteHighlighterStrokeRenderer* highlighterstrokerenderer;
    static SGWidget000133103* favouritetoolsbackground;
    static SGScrollView000231100* favouritetoolsscrollview;
    static SGLayoutFavouriteTools* favouritetoolslayout;
    static SGIconButton022111132* favouritetoolsaddbutton;
    static SGIconButton022111132* favouritetoolsremovebutton;
    static void deleteselectors();

private:
    SGNoteViewManagement(){}
    ~SGNoteViewManagement(){}
};

#endif // SGNOTEVIEWMANAGEMENT_H
