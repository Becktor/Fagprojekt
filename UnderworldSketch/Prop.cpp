#include "Geo.h"
#include "Prop.h"

Prop::Prop(byte width, byte height) : _hitbox(0, 0, width, height) {
  _levitate = false;
  _xVel = 0;
  _yVel = 0;
}

void Prop::hit(byte damage, char force) { }

/*
void Prop::translate(int x, int y) {
  _hitbox._x += x;
  _hitbox._y += y;
  //_hitbox.translate(x, y);
}
*/
