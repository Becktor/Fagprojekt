#include "Direction.h"
#include "Geo.h"
#include "Logic.h"
#include "Unit.h"

Unit::Unit(Rect hitbox) {
  _hitbox = hitbox;
  _xVel = 0;
  _yVel = 0;
  _dir = Left;
}

Direction Unit::getDir() {
  return _dir;
}

Rect* Unit::getHitbox() {
  return &_hitbox;
}

int Unit::getXVel() {
  return _xVel;  
}

int Unit::getYVel() {
  return _yVel;
}

void Unit::setDir(Direction dir) {
  _dir = dir;
}

void Unit::setXVel(int xVel) {
   _xVel = xVel;  
}

void Unit::setYVel(int yVel) {
   _yVel = yVel;
}

void Unit::toggleDir() {
  if(_dir == Left)
    _dir = Right;
  else
    _dir = Left;
}

void Unit::translate(int x, int y) {
  _hitbox.translate(x, y);
}

void Unit::updateAI(int dTime, Logic *logic) { }

//Should be moved to the future prop class when made.
//Moves the unit according to his velocity
void Unit::updatePhysics(int dTime, Logic *logic) { //dTime isn't used
  logic->gravitate(this, dTime);
  if(!logic->moveUnitHoriz(this, getXVel()))
    setXVel(0);
  if(!logic->moveUnitVerti(this, getYVel()))
    setYVel(0);
}
