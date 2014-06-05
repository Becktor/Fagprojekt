#ifndef prop_h
#define prop_h

#include "Geo.h"

class Prop {
  private:
    boolean _levitate;
    char _xVel, _yVel;
    Rect _hitbox;
  public:
    Prop(byte width, byte height);
    Rect* getHitbox();
    boolean getLevitate();
    char getXVel();
    char getYVel();
    virtual void hit(byte damage, char force);
    void setXVel(char yVel);
    void setYVel(char yVel);
    void translate(int x, int y);
};
#endif
