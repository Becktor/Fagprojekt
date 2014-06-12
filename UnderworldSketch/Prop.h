#ifndef prop_h
#define prop_h

#include "Geo.h"

class Prop {
  public:
    boolean _levitate, _wait;
    byte _imageWidth, _handle, _cells, _currentCell;
    char _dir, _xVel, _yVel;
    byte _FR, _aniTime;
    Rect _hitbox;

    Prop(byte width, byte height, byte imageWidth);
    virtual void collideX();
    virtual void collideY();
    virtual void hit(byte damage, char force);
    virtual void initialize();
    void newHandle(byte handle, byte cell, byte FR);
    void updateAnimation(byte dTime);
    char zoomIn(byte change, char current, char target);
};
#endif
