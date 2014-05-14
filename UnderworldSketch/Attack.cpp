#include "Geo.h"
#include "Unit.h"
#include "Attack.h"

Attack::Attack(int x, int y, int width, int height, int damage, Unit *owner) : _area(x, y, width, height) {
  //_area = area;
  _damage = damage;
  _owner = owner;
}

int Attack::getDamage() {
  return _damage;
}

Unit* Attack::getOwner() {
  return _owner;
}

Rect* Attack::getArea() {
  return &_area;
}
