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
    int _speed;
    int _Yacc;
    Direction _dir;
    Rect _hitbox;

  public:
    Unit(int speed, Rect hitbox);
    Direction getDir();
    int getSpeed();
    int getYacc();
    void setSpeed(int speedValue);
    void setAcc(int accValue);
    Rect getHitbox();
    void toggleDir();
    void translate(int x, int y);
    void update(int dTime, Logic logic);
};
#endif
