#include "Direction.h"
#include "Geo.h"
#include "Logic.h"
#include "Unit.h"
#include "Prop.h"

Unit::Unit(Rect hitbox, int health) : Prop(hitbox) {
  _health = health;
  _xVel = 0;
  _yVel = 0;
  _dir = LEFT;
}

void Unit::damage(int damage) {
  _health -= damage;
}

Direction Unit::getDir() {
  return _dir;
}

boolean Unit::getLevitate() {
  return _levitate;
}

int Unit::getXVel() {
  return _xVel;  
}

int Unit::getYVel() {
  return _yVel;
}

boolean Unit::isDead() {
  return _health <= 0;
}

void Unit::setDir(Direction dir) {
  _dir = dir;
}

void Unit::setLevitate(boolean levitate) {
  _levitate = levitate;
}

void Unit::setXVel(int xVel) {
   _xVel = xVel;  
}

void Unit::setYVel(int yVel) {
   _yVel = yVel;
}

void Unit::toggleDir() {
  if(_dir == LEFT)
    _dir = RIGHT;
  else
    _dir = LEFT;
}

void Unit::updateAI(int dTime, Logic *logic) { }

//Should be moved to the future prop class when made.
//Moves the unit according to his velocity
void Unit::updatePhysics(int dTime, Logic *logic) { //dTime isn't used
  if(!_levitate)
    logic->gravitate(this, dTime);
  if(!logic->moveUnitHoriz(this, getXVel()))
    setXVel(0);
  if(!logic->moveUnitVerti(this, getYVel()))
    setYVel(0);
}
