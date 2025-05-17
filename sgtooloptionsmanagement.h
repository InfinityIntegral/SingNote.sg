#ifndef SGTOOLOPTIONSMANAGEMENT_H
#define SGTOOLOPTIONSMANAGEMENT_H

#include <QObject>
#include "sgwidget000221104.h"
#include "sgtextbutton022211332.h"
#include "sgtextbutton022211232.h"
#include "sgtextbutton022314332.h"
#include "sgscrollview000231100.h"
#include "sglayoutchangepen.h"
#include "sgtext012110021.h"
#include "sginputfield122110032.h"
#include "sginputfield222110032.h"
#include "sgwidget000221103.h"
#include "sglayoutchangeeraser.h"
#include "sgtextbutton022110032.h"
#include "sglayoutchangehighlighter.h"
#include "sglayoutchangeselector.h"

class SGToolOptionsManagement : public QObject
{
    Q_OBJECT
public:
    static void showtooloptions();
    static SGWidget000221104* changetoolbackground;
    static SGTextButton022211332* changetoolcancelbutton;
    static void changetoolcancel();
    static SGTextButton022211232* changetoolmovebutton;
    static SGTextButton022211232* changetoolpenbutton;
    static SGTextButton022211232* changetoolhighlighterbutton;
    static SGTextButton022211232* changetooleraserbutton;
    static SGTextButton022211232* changetoolselectorbutton;
    static SGTextButton022211232* changetoolshapebutton;
    static SGTextButton022211232* changetoollaserpenbutton;
    static SGTextButton022211232* changetoollaserpointerbutton;
    static void updatechangetoolicon();
    static void changetoolmove();
    static SGWidget000221103* changepenbackground;
    static void showchangepen();
    static SGTextButton022314332* changepencancelbutton;
    static SGTextButton022314332* changepenconfirmbutton;
    static void changepencancel();
    static SGScrollView000231100* changepenscrollview;
    static SGLayoutChangePen* changepenlayout;
    static SGText012110021* changepentitletext;
    static SGText012110021* changepencolourtext;
    static SGInputField122110032* changepenredinput;
    static SGInputField122110032* changepengreeninput;
    static SGInputField122110032* changepenblueinput;
    static SGText012110021* changepenwidthtext;
    static SGInputField222110032* changepenwidthinput;
    static void changepenconfirm();
    static void showchangeeraser();
    static SGWidget000221103* changeeraserbackground;
    static SGTextButton022314332* changeerasercancelbutton;
    static SGTextButton022314332* changeeraserconfirmbutton;
    static void changeerasercancel();
    static void changeeraserconfirm();
    static SGScrollView000231100* changeeraserscrollview;
    static SGLayoutChangeEraser* changeeraserlayout;
    static SGText012110021* changeerasertitletext;
    static SGText012110021* changeeraserwidthtext;
    static SGInputField222110032* changeeraserwidthinput;
    static SGTextButton022110032* changeerasercompletebutton;
    static SGTextButton022110032* changeeraserpartialbutton;
    static SGTextButton022110032* changeeraserhighlighterbutton;
    static SGTextButton022110032* changeerasereverythingbutton;
    static int tooltypeindicator;
    static void changeerasercomplete();
    static void changeeraserpartial();
    static void changeerasereverything();
    static void changeeraserhighlighter();
    static void showchangehighlighter();
    static SGWidget000221103* changehighlighterbackground;
    static SGTextButton022314332* changehighlightercancelbutton;
    static SGTextButton022314332* changehighlighterconfirmbutton;
    static void changehighlightercancel();
    static void changehighlighterconfirm();
    static SGScrollView000231100* changehighlighterscrollview;
    static SGLayoutChangeHighlighter* changehighlighterlayout;
    static SGText012110021* changehighlightertitletext;
    static SGText012110021* changehighlightercolourtext;
    static SGInputField122110032* changehighlighterredinput;
    static SGInputField122110032* changehighlightergreeninput;
    static SGInputField122110032* changehighlighterblueinput;
    static SGInputField122110032* changehighlightertransparencyinput;
    static SGText012110021* changehighlighterwidthtext;
    static SGInputField222110032* changehighlighterwidthinput;
    static void showchangeselector();
    static SGWidget000221103* changeselectorbackground;
    static SGTextButton022314332* changeselectorcancelbutton;
    static SGTextButton022314332* changeselectorconfirmbutton;
    static void changeselectorcancel();
    static void changeselectorconfirm();
    static SGScrollView000231100* changeselectorscrollview;
    static SGLayoutChangeSelector* changeselectorlayout;
    static SGText012110021* changeselectortitletext;
    static SGTextButton022110032* changeselectorpenstrokebutton;
    static SGTextButton022110032* changeselectorboxbutton;
    static SGTextButton022110032* changeselectorglobalbutton;
    static SGTextButton022110032* changeselectorshapebutton;
    static void changeselectorpenstroke();
    static void changeselectorbox();
    static void changeselectorglobal();
    static void changeselectorshape();

private:
    SGToolOptionsManagement(){}
    ~SGToolOptionsManagement(){}
};

#endif // SGTOOLOPTIONSMANAGEMENT_H
