/*
 *  Currently non-abstract class of any one unit. Cannot be superclass
 *  to 'Entities' since entities uses points for positions while units use
 *  hitboxes. Could be superclass to future prop though.
 */

#ifndef unit_h
#define unit_h

#include "Arduino.h"
#include "Geo.h"

class Unit
{
  private:
    Rect _hitbox;
  
  public:
    Unit(Rect hitbox);
    Rect getHitbox();
};

#endif
