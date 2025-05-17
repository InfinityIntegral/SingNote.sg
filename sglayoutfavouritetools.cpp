#include "sglayoutfavouritetools.h"
#include <QTimer>
#include "sgcentralmanagement.h"

SGLayoutFavouriteTools::SGLayoutFavouriteTools(QWidget *parent){
    (*this).setParent(parent);
    (*this).objlist = new QVector<QWidget*>();
    (*this).show();
    (*this).ReceiveUpdateCall();
}

SGLayoutFavouriteTools::~SGLayoutFavouriteTools(){
    delete (*this).objlist;
}

void SGLayoutFavouriteTools::ReceiveUpdateCall(){
    (*this).move(QPoint(0.0f, 0.0f));
    (*this).resize(QSize((*parentWidget()).width(), 1.5f * SGCentralManagement::sizeunit * (float)std::ceil(0.5f * (float)((*objlist).size()))));
    QTimer::singleShot(0, this, &SGLayoutFavouriteTools::ResizeObj);
}

void SGLayoutFavouriteTools::ResizeObj(){
    for(int i=0; i<(*objlist).size(); i++){
        (*(*objlist)[i]).move(QPoint(1.5f * SGCentralManagement::sizeunit * (float)(i % 2), 1.5f * SGCentralManagement::sizeunit * (float)(i / 2)));
    }
}
