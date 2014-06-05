#include "Geo.h"
#include "Prop.h"

Prop::Prop(byte width, byte height) : _hitbox(0, 0, width, height) { }

Rect* Prop::getHitbox() {
  return &_hitbox;
}

void Prop::translate(int x, int y) {
  _hitbox.translate(x, y);
}
