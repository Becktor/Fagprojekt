#ifndef attack_h
#define attack_h

#include "Geo.h"

class Unit;
class Attack {
  public:
    byte _damage;
    Unit *_owner;
    Rect _area;
    Attack(int x, int y, byte width, byte height, byte damage, Unit *owner);
};
#endif
