#include "Direction.h"
#include "Geo.h"
#include "Logic.h"
#include "Unit.h"

Unit::Unit(int moveSpeed, Rect hitbox) {
  _moveSpeed = moveSpeed;
  _hitbox = hitbox;
  _dir = Left;
  _falling = false;
}

void Unit::accelerateY(int dY) {
  setYVel(_yVel + dY);
}

Direction Unit::getDir() {
  return _dir;
}

Rect* Unit::getHitbox() {
  return &_hitbox;
}

int Unit::getMoveSpeed() {
  return _moveSpeed;
}

int Unit::getYVel(){
  return _yVel; 
}

boolean Unit::isFalling() {
  return _falling;
}

void Unit::setYVel(int yVel){
   _yVel = max(min(yVel, -TERMINAL_VEL), TERMINAL_VEL); 
}

void Unit::toggleDir() {
  if(_dir = Left)
    _dir = Right;
  else
    _dir = Left;
}

void Unit::setFalling(boolean falling) {
  _falling = falling;
}

void Unit::translate(int x, int y) {
  _hitbox.translate(x, y);
}

void Unit::update(int dTime, Logic logic) { //dtime is still unused
  if(!logic.moveUnitHoriz(this, _moveSpeed * _dir))
    toggleDir();   
}
