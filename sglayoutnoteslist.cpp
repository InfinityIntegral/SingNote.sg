#include "sglayoutnoteslist.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"

SGLayoutNotesList::SGLayoutNotesList(QWidget *parent){
    (*this).setParent(parent);
    (*this).n = 0;
    (*this).buttonslist = nullptr;
    (*this).show();
    (*this).ReceiveUpdateCall();
}

SGLayoutNotesList::~SGLayoutNotesList(){
    delete[] (*this).buttonslist;
}

void SGLayoutNotesList::ReceiveUpdateCall(){
    (*this).move(QPoint(0.0f, 0.0f));
    QTimer::singleShot(0, this, &SGLayoutNotesList::ResizeObj);
}

void SGLayoutNotesList::ResizeObj(){
    int k = (*parentWidget()).size().width() / (4.0f * SGCentralManagement::sizeunit);
    int v = n/k + 1;
    (*this).resize(QSize((*parentWidget()).size().width(), (float)v * 7.0f * SGCentralManagement::sizeunit));
    for(int i=0; i<n; i++){
        int q = i/k;
        int r = i%k;
        (*(*this).buttonslist[i]).move(QPoint((float)r * 4.0f * SGCentralManagement::sizeunit, (float)q * 7.0f * SGCentralManagement::sizeunit));
    }
}
