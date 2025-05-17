#include "sglayoutnotetoolbar.h"
#include <QTimer>

SGLayoutNoteToolbar::SGLayoutNoteToolbar(QWidget *parent){
    (*this).setParent(parent);
    (*this).cnt = 2;
    (*this).objlist = new QWidget*[(*this).cnt];
    (*this).show();
    (*this).ReceiveUpdateCall();
}

SGLayoutNoteToolbar::~SGLayoutNoteToolbar(){
    delete[] (*this).objlist;
}

void SGLayoutNoteToolbar::ReceiveUpdateCall(){
    (*this).move(QPoint(0.0f, 0.0f));
    (*this).resize((*parentWidget()).size());
    QTimer::singleShot(0, this, &SGLayoutNoteToolbar::ResizeObj);
}

void SGLayoutNoteToolbar::ResizeObj(){
    float bw = (*(*this).objlist[0]).size().width();
    int n = (int)std::floor((*this).size().height() / bw);
    for(int i=0; i<(*this).cnt; i++){
        int r = i%n;
        int q = (i - r)/n;
        (*(*this).objlist[i]).move(QPoint(q * bw, r * bw));
    }
}
