#ifndef prop_h
#define prop_h

#include "Geo.h"

class Prop {
  public:
    byte _imageWidth, _handle, _cells, _currentCell;
    long _FR, _millis;
    boolean _levitate;
    char _xVel, _yVel,_dir;
    Rect _hitbox;

    Prop(byte width, byte height, byte imageWidth);
    void accelerate(byte acc, char targetSpeed);
    void checkFrameChange(long milis);
    void updateHandle(byte handle, byte cell);
    virtual void hit(byte damage, char force);
    virtual void initialize();
    virtual void xCollide();
    virtual void yCollide();
};
#endif
