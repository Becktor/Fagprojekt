#include "Direction.h"
#include "Logic.h"
#include "Unit.h"
#include "Prop.h"

Unit::Unit(int x, int y, byte width, byte height, char health) : Prop(x, y, width, height) {
  _health = health;
  _dir = LEFT;
  _levitate = false;
  _handle = 0;
  _cells = 0;
}

void Unit::damage(byte damage) {
  _health -= damage;
}

Direction Unit::getDir() {
  return _dir;
}

boolean Unit::getLevitate() {
  return _levitate;
}

char Unit::getXVel() {
  return _xVel;  
}

char Unit::getYVel() {
  return _yVel;
}

int Unit::getHandle() {
  return _handle;
}

int Unit::getCells() {
  return _cells;
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

void Unit::setXVel(char xVel) {
   _xVel = xVel;  
}

void Unit::setYVel(char yVel) {
   _yVel = yVel;
}

void Unit::setHandle(int handle) {
   _handle = handle;
}

void Unit::setCells(int cells) {
   _cells = cells;
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

