#include "Direction.h"
#include "Logic.h"
#include "Prop.h"
#include "Unit.h"

Unit::Unit(byte width, byte height, byte health, byte score, byte imageWidth, word invTime) : Prop(width, height, imageWidth, invTime) {
  _health = health;
  _score = score;
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

void Unit::initialize() {
  Prop::initialize();
  _isScored = false;
}

void Unit::toggleDir() {
  _dir = -_dir;
}

void Unit::updateAI(byte dTime, Logic *logic) { }
