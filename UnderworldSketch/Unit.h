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
#include "Prop.h"

class Logic;
class Unit : public Prop
{
  private:
    Direction _dir;
    boolean _levitate;
    int _xVel, _yVel;

  public:
    Unit(Rect hitbox);
    Direction getDir();
    boolean getLevitate();
    int getXVel();
    int getYVel();
    void setDir(Direction dir);
    void setLevitate(boolean levitate);
    void setXVel(int yVel);
    void setYVel(int yVel);
    void toggleDir();
    virtual void updateAI(int dTime, Logic *logic);
    void updatePhysics(int dTime, Logic *logic);
};

#endif
