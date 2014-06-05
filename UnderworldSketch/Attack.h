#ifndef attack_h
#define attack_h

#include "Geo.h"
#include "Prop.h"

class Attack {
  public:
    Rect *_area;
    byte _damage,
         _force;
    Prop *_owner;
    Attack(Rect* area, byte damage, byte force, Prop *owner);
};
#endif
