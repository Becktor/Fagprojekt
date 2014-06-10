#include "Direction.h"
#include "Logic.h"
#include "Prop.h"
#include "Unit.h"

Unit::Unit(byte width, byte height, char health, byte imageWidth) : Prop(width, height) {
  _health = health;
  _dir = randDir();
  _imageWidth = imageWidth;
  _handle = 0;
  _cells = 0;
}

void Unit::hit(byte damage, char force) {
  if(damage >= _health)
    _health = 0;
  else
    _health -= damage;
  _xVel = force;
}

void Unit::fillHealth() {}

void Unit::toggleDir() {
  _dir = -1 * _dir;
}

void Unit::updateAI(int dTime, Logic *logic) { }

void Unit::xCollide() {
  _xVel = 0;
}

void Unit::yCollide() {
  _yVel = 0;
}
