#include "Direction.h"
#include "Geo.h"
#include "Logic.h"
#include "Unit.h"

Unit::Unit(int speed, Rect hitbox) {
  _speed = speed;
  _hitbox = hitbox;
}

Direction Unit::getDir() {
  return _dir;
}

Rect Unit::getHitbox() {
  return _hitbox;
}

int Unit::getSpeed() {
  return _speed;
}

void Unit::toggleDir() {
  if(_dir = Left)
    _dir = Right;
  else
    _dir = Left;
}

void Unit::translate(int x, int y) {
  _hitbox.translate(x, y);
}

void Unit::update(int dTime, Logic logic) { //dtime is still unused
  if(!logic.moveUnitHoriz(this, _speed * _dir))
    toggleDir();
}
