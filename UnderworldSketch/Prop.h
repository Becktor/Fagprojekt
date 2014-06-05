#ifndef prop_h
#define prop_h

#include "Geo.h"

class Prop {
  private:
    Rect _hitbox;
  public:
    Prop(byte width, byte height);
    Rect* getHitbox();
    void translate(int x, int y);
};
#endif
