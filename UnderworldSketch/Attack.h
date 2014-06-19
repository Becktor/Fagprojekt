/*
 *  Object containing all attack data, used in lists.
 */

#ifndef attack_h
#define attack_h

#include "Geo.h"
#include "Prop.h"

class Attack {
  public:
    Rect *_area; //Attack area
    byte _damage;
    char _force; //Directional force, used in both dimensions. y-axis force is always upwards.
    Prop *_owner; //The owner of the attack, immune.
    Attack(Rect* area, byte damage, char force, Prop *owner);
};
#endif
