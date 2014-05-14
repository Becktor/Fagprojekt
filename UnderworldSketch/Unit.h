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
class Unit : public Prop {
  private:
    Direction _dir;
    boolean _levitate;
    char _health, _xVel, _yVel;

  public:
    Unit(int x, int y, byte width, byte height, char health);
    void damage(byte damage);
    Direction getDir();
    boolean getLevitate();
    char getXVel();
    char getYVel();
    boolean isDead();
    void setDir(Direction dir);
    void setLevitate(boolean levitate);
    void setXVel(char yVel);
    void setYVel(char yVel);
    void toggleDir();
    virtual void updateAI(int dTime, Logic *logic);
    void updatePhysics(int dTime, Logic *logic);
};

#endif
