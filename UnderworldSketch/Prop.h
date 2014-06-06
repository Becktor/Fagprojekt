#ifndef prop_h
#define prop_h

#include "Geo.h"

class Prop {
  public:
    boolean _levitate;
    char _xVel, _yVel;
    Rect _hitbox;

    Prop(byte width, byte height);
    virtual void hit(byte damage, char force);
    //void translate(int x, int y);
};
#endif
