#include "Geo.h"
#include "Unit.h"

#ifndef attack_h
#define attack_h

class Unit;
class Attack
{
  private:
    int _damage;
    Unit *_owner;
    Rect _area;
  
  public:
    Attack(int damage, Unit *owner, Rect area);
    int getDamage();
    Unit* getOwner();
    Rect* getArea();
};

#endif
