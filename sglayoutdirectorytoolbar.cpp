#include "sglayoutdirectorytoolbar.h"
#include <QTimer>
#include "sgdirectoryviewmanagement.h"

SGLayoutDirectoryToolbar::SGLayoutDirectoryToolbar(QWidget *parent){
    (*this).setParent(parent);
    (*this).cnt = 3;
    (*this).objlist = new QWidget*[(*this).cnt];
    (*this).show();
    (*this).ReceiveUpdateCall();
}

SGLayoutDirectoryToolbar::~SGLayoutDirectoryToolbar(){
    delete[] (*this).objlist;
}

void SGLayoutDirectoryToolbar::ReceiveUpdateCall(){
    (*this).move(QPoint(0.0f, 0.0f));
    (*this).resize((*parentWidget()).size());
    QTimer::singleShot(0, this, &SGLayoutDirectoryToolbar::ResizeObj);
}

void SGLayoutDirectoryToolbar::ResizeObj(){
    float bw = (*(*this).objlist[0]).size().width();
    int n = (int)std::floor((*this).size().height() / bw);
    for(int i=0; i<(*this).cnt; i++){
        int r = i%n;
        int q = (i - r)/n;
        (*(*this).objlist[i]).move(QPoint((*this).size().width() - (q+1) * bw, r * bw));
    }
}
