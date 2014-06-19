#include "Direction.h"
#include "Logic.h"
#include "Prop.h"
#include "Unit.h"

Unit::Unit(byte width, byte height, byte health, byte score, byte imageWidth, byte imageHeight, word invTime) : Prop(width, height, imageWidth, imageHeight, invTime) {
  _health = health;
  _score = score;
}

//Horizontal collision function.
//Called when colliding in the x-axis
void Unit::collideX() {
  _xVel = 0;
}

//Vertical collision function.
//Called when colliding in the y-axis
void Unit::collideY() {
  _yVel = 0;
}

//Hit function.
//Called when attacked, if not invulnerable.
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
