#include "Direction.h"
#include "Logic.h"
#include "Prop.h"
#include "Unit.h"

Unit::Unit(byte width, byte height, char health, byte imageWidth) : Prop(width, height, imageWidth) {
  _health = health;
}

void Unit::hit(byte damage, char force) {
  Prop::hit(damage, force);
  if(damage >= _health)
    _health = 0;
  else
    _health -= damage;
}

void Unit::fillHealth() {}

void Unit::toggleDir() {
  _dir = -1 * _dir;
}

void Unit::updateHandle(byte handle, byte cells) {
  _handle = handle;
  _cells = cells;
  _currentCell = 0;
}


void Unit::updateAI(int dTime, Logic *logic) { }

void Unit::xCollide() {
  _xVel = 0;
}

void Unit::yCollide() {
  _yVel = 0;
}
