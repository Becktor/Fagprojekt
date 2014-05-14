#include "Geo.h"
#include "Unit.h"

#ifndef attack_h
#define attack_h

class Unit;
class Attack
{
  private:
    byte _damage;
    Unit *_owner;
    Rect _area;
  
  public:
    Attack(int x, int y, byte width, byte height, byte damage, Unit *owner);
    byte getDamage();
    Unit* getOwner();
    Rect* getArea();
};

#endif
