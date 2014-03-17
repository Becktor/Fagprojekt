#include "Geo.h"
#include "Director.h"
#include "Unit.h"

Unit::Unit(int speed, Rect hitbox) {
  _speed = speed;
  _hitbox = hitbox;
}

Rect Unit::getHitbox() {
  return _hitbox;
}

void Unit::translate(int x, int y) {
  _hitbox.translate(x, y);
}

void Unit::update(Logic direct) {
  //logic.moveUnit(this);
}
