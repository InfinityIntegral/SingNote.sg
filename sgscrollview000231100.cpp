#include "sgscrollview000231100.h"
#include "sggenerallibrary.h"
#include "sgcentralmanagement.h"

SGScrollView000231100::SGScrollView000231100(QWidget *parent, float x, float y, float h1, float h0){
    (*this).setParent(parent);
    (*this).x = x;
    (*this).y = y;
    (*this).h1 = h1;
    (*this).h0 = h0;
    (*this).show();
    SGGeneralLibrary::setscrollviewstylesheet(this);
    (*this).setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    (*this).setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    (*this).setFrameStyle(QFrame::NoFrame);
    (*this).ResizeObj();
}

void SGScrollView000231100::ResizeObj(){
    (*this).move(QPoint(x * SGCentralManagement::sizeunit, y * SGCentralManagement::sizeunit));
    (*this).resize(QSize((*parentWidget()).size().width(), h1 * (*parentWidget()).size().height() + h0 * SGCentralManagement::sizeunit));
    SGGeneralLibrary::updatescrollbarwidth(this);
}
