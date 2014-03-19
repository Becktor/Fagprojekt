/*
 *  Currently non-abstract class of any one unit. Cannot be superclass
 *  to 'Entities' since entities uses points for positions while units use
 *  hitboxes. Could be superclass to future prop though.
 */

#ifndef unit_h
#define unit_h

#include "Geo.h"
#include "Logic.h"

class Logic;
class Unit
{
  private:
    boolean _dir; //false = left, true = right. Use enum?
    int _speed;
    Rect _hitbox;

  public:
    Unit(int speed, Rect hitbox);
    boolean getDir();
    int getSpeed();
    Rect getHitbox();
    void translate(int x, int y);
    void update(Logic direct);
};

#endif
