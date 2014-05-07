#include "Direction.h"
#include "Geo.h"
#include "Prop.h"

Prop::Prop(Rect hitbox){
  _hitbox=hitbox;
  
}

Rect* Prop::getHitbox() {
  return &_hitbox;
}

void Prop::translate(int x, int y) {
  _hitbox.translate(x, y);
}


