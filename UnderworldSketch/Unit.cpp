#include "Direction.h"
#include "Geo.h"
#include "Logic.h"
#include "Unit.h"

Unit::Unit(int moveSpeed, Rect hitbox) {
  _moveSpeed = moveSpeed;
  _hitbox = hitbox;
  _dir=Left;
}

Direction Unit::getDir() {
  return _dir;
}

Rect Unit::getHitbox() {
  return _hitbox;
}

int Unit::getMoveSpeed() {
  return _moveSpeed;
}

int Unit::getYAcc(){
  return _YAcc; 
}

void Unit::setYAcc(int YAcc){
   _YAcc = YAcc; 
}

void Unit::toggleDir() {
  if(_dir = Left)
    _dir = Right;
  else
    _dir = Left;
}

void Unit::translate(int x, int y) {
  _hitbox.translate(x, y);
}

void Unit::update(int dTime, Logic logic) { //dtime is still unused
  if(!logic.moveUnitHoriz(this, _speed * _dir))
    toggleDir();   
}
