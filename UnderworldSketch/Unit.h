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

#define TERMINAL_VEL 10

class Logic;
class Unit
{
  private:
    boolean _falling;
    int _moveSpeed; //Should be constant. When unit becomes an abstract class, move this value to individual creature constants.
    int _yVel; //Should be 2dimensional in the future.
    Direction _dir;
    Rect _hitbox;

  public:
    Unit(int speed, Rect hitbox);
    void accelerateY(int dY);
    Direction getDir();
    Rect* getHitbox();
    int getMoveSpeed();
    int getYVel();
    boolean isFalling();
    void setFalling(boolean falling);
    void setYVel(int yVel);
    void toggleDir();
    void translate(int x, int y);
    void update(int dTime, Logic logic);
};
#endif
