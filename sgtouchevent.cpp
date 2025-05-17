#include "sgtouchevent.h"

int SGTouchEvent::TouchStart = 1;
int SGTouchEvent::TouchOngoing = 2;
int SGTouchEvent::TouchEnd = 3;

SGTouchEvent::SGTouchEvent(int id, int tp, bool pen, float x, float y){
    (*this).id = id;
    (*this).phase = tp;
    (*this).pen = pen;
    (*this).x = x;
    (*this).y = y;
}
