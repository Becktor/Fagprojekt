#include "Geo.h"
#include "Unit.h"
#include "Attack.h"

Attack::Attack(int damage, Unit *owner, Rect area) {
  _damage = damage;
  _owner = owner;
  _area = area;
  
  
  
  
  
  
  
  
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
