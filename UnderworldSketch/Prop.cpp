#include "Geo.h"
#include "Prop.h"

Prop::Prop(int x, int y, byte width, byte height) : _hitbox(x, y, width, height) { }

Rect* Prop::getHitbox() {
  return &_hitbox;
}

void Prop::translate(int x, int y) {
  _hitbox.translate(x, y);
}



