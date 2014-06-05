#include "Geo.h"
#include "Attack.h"

Attack::Attack(Rect* area, byte damage, byte force, Prop *owner) {
  _area = area;
  _damage = damage;
  _force = force;
  _owner = owner;
}
