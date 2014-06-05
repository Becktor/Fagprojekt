#include "Geo.h"
#include "Attack.h"

Attack::Attack(int x, int y, byte width, byte height, byte damage, Prop *owner) : _area(x, y, width, height) {
  _damage = damage;
  _owner = owner;
}
