#ifndef attack_h
#define attack_h

#include "Geo.h"
#include "Prop.h"

class Attack {
  public:
    byte _damage;
    Prop *_owner;
    Rect _area;
    Attack(int x, int y, byte width, byte height, byte damage, Prop *owner);
};
#endif
