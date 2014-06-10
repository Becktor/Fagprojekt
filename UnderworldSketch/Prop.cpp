#include "Geo.h"
#include "Prop.h"

Prop::Prop(byte width, byte height) : _hitbox(width, height) {
  _levitate = false;
  _xVel = 0;
  _yVel = 0;
}

void Prop::accelerate(byte acc, char targetSpeed) {
  if(targetSpeed > _xVel)
    _xVel = min(_xVel + acc, targetSpeed);
  else if(targetSpeed < _xVel)
    _xVel = max(_xVel - acc, targetSpeed);
}

void Prop::hit(byte damage, char force) { }

void Prop::xCollide() { }

void Prop::yCollide() { }
