#ifndef SGTOUCHEVENT_H
#define SGTOUCHEVENT_H

class SGTouchEvent
{
public:
    SGTouchEvent(int id, int tp, bool pen, float x, float y);
    static int TouchStart;
    static int TouchOngoing;
    static int TouchEnd;
    int id;
    int phase;
    bool pen;
    float x;
    float y;
};

#endif // SGTOUCHEVENT_H
