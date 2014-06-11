#include "Direction.h"
#include "Logic.h"
#include "Prop.h"
#include "Unit.h"

Unit::Unit(byte width, byte height, char health, byte imageWidth) : Prop(width, height, imageWidth) {
  _health = health;
}

void Unit::collideX() {
  _xVel = 0;
}

void Unit::collideY() {
  _yVel = 0;
}

void Unit::hit(byte damage, char force) {
  Prop::hit(damage, force);
  if(damage >= _health)
    _health = 0;
  else
    _health -= damage;
}

void Unit::toggleDir() {
  _dir = -1 * _dir;
}

void Unit::updateAI(int dTime, Logic *logic) { }
