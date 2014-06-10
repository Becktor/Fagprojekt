#include "Direction.h"
#include "Logic.h"
#include "Prop.h"
#include "Unit.h"

Unit::Unit(byte width, byte height, char health, byte imageWidth) : Prop(width, height) {
  _health = health;
  _dir = LEFT;
  _imageWidth = imageWidth;
  _handle = 0;
  _cells = 0;
  _currentCell = 0;
  _FR = 0;
  _millis = 0;
}

void Unit::hit(byte damage, char force) {
  _health -= damage;
  _xVel = force;
}

char Unit::getDir() {
  return _dir;
}

int Unit::getHandle() {
  return _handle;
}

int Unit::getCells() {
  return _cells;
}

int Unit::getCurrentCell() {
  return _currentCell;
}

int Unit::getFR() {
  return _FR;
}

boolean Unit::isDead() {
  return _health <= 0;
}

void Unit::fillHealth() {}

void Unit::setDir(Direction dir) {
  _dir = dir;
}

void Unit::setHealth(char health) {
  _health = health;
}

void Unit::setHandle(int handle) {
   _handle = handle;
}

void Unit::setCells(int cells) {
   _cells = cells;
}

void Unit::setCurrentCell(int currentCell) {
   _currentCell = currentCell;
}

void Unit::setFR(long frameRate) {
   _FR = frameRate;
}

void Unit::toggleDir() {
  _dir = _dir * -1;
}

void Unit::checkFrameChange(long milis) {
  if((milis - _millis) > _FR)
  {   
   _millis = milis;
   if(_currentCell == _cells)
    _currentCell = 0; 
   else
    _currentCell++; 
  }
}


void Unit::updateAI(int dTime, Logic *logic) { }

void Unit::xCollide() {
  _xVel = 0;
}

void Unit::yCollide() {
  _yVel = 0;
}
