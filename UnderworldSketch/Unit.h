/*
 *  Currently non-abstract class of any one unit. Cannot be superclass
 *  to 'Entities' since entities uses points for positions while units use
 *  hitboxes. Could be superclass to future prop though.
 */

#ifndef unit_h
#define unit_h

#include "Direction.h"
#include "Geo.h"
#include "Logic.h"

class Logic;
class Unit
{
  private:
    int _xVel;
    int _yVel;
    Rect _hitbox;

  public:
    Unit(Rect hitbox);
    Rect* getHitbox();
    int getXVel();
    int getYVel();
    void setXVel(int yVel);
    void setYVel(int yVel);
    void translate(int x, int y);
    virtual void updateAI(int dTime, Logic *logic);
    void updatePhysics(int dTime, Logic *logic);
};
#endif
