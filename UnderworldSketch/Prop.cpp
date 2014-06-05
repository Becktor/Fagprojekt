#include "Geo.h"
#include "Prop.h"

Prop::Prop(byte width, byte height) : _hitbox(0, 0, width, height) {
  _levitate = false;
  _xVel = 0;
  _yVel = 0;
}

Rect* Prop::getHitbox() {
  return &_hitbox;
}

boolean Prop::getLevitate() {
  return _levitate;
}

char Prop::getXVel() {
  return _xVel;  
}

char Prop::getYVel() {
  return _yVel;
}

void Prop::setXVel(char xVel) {
  _xVel = xVel;  
}

void Prop::setYVel(char yVel) {
  _yVel = yVel;
}

void Prop::translate(int x, int y) {
  _hitbox.translate(x, y);
}
