#ifndef prop_h
#define prop_h

#include "Geo.h"

class Prop {
  public:
    boolean _levitate, //Unused, if true the prop is not affected by gravity.
            _animLock, //If true, then the prop cannot change animation until it ends the current anmation.
            _animStop, //If true, then the animation stops at the last frame of current animation.
            _invulnerable; //If true, cannot be hit.
    byte _imageWidth, //Sprite dimensions.
         _imageHeight,
         _handle, //Sprite handle.
         _cells, //Sprite cells.
         _currentCell; //Current animation frame.
    char _dir, //Direction, used in movement and drawing.
         _xVel, //Velocities.
         _yVel;
    word _FR, _animTime, _invTime, _invTimer;
    Rect _hitbox;

    Prop(byte width, byte height, byte imageWidth, byte imageHeight, word invTim);
    virtual void collideX();
    virtual void collideY();
    virtual void hit(byte damage, char force);
    virtual void initialize();
    void newHandle(byte handle, byte cell, word FR);
    void push(char force);
    void updateAnimation(byte dTime);
    void updateInvulnerability(byte dTime);
    char zoomIn(byte change, char current, char target);
};
#endif
