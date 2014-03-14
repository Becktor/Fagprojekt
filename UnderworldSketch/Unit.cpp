#include "Arduino.h"
#include "Geo.h"
#include "Unit.h"

Unit::Unit(Rect hitbox) {
  _hitbox = hitbox;
}

Rect Unit::getHitbox() {
  return _hitbox;
}
