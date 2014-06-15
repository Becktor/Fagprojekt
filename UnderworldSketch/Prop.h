#ifndef prop_h
#define prop_h

#include "Geo.h"

class Prop {
  public:
    boolean _levitate, _animLock, _animStop, _invulnerable;
    byte _imageWidth, _handle, _cells, _currentCell;
    char _dir, _xVel, _yVel;
    word _FR, _animTime, _invTime, _invTimer;
    Rect _hitbox;

    Prop(byte width, byte height, byte imageWidth, word invTim);
    virtual void collideX();
    virtual void collideY();
    virtual void hit(byte damage, char force);
    virtual void initialize();
    void newHandle(byte handle, byte cell, word FR);
    void updateAnimation(byte dTime);
    void updateInvulnerability(byte dTime);
    char zoomIn(byte change, char current, char target);
};
#endif
