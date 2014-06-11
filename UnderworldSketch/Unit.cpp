#include "Direction.h"
#include "Logic.h"
#include "Prop.h"
#include "Unit.h"

Unit::Unit(byte width, byte height, char health, byte imageWidth) : Prop(width, height) {
  _imageWidth = imageWidth;
  _health = health;
  initialize();
}

void Unit::hit(byte damage, char force) {
  Prop::hit(damage, force);
  if(damage >= _health)
    _health = 0;
  else
    _health -= damage;
}

int Unit::getCurrentCell() {
  return _currentCell;
}

int Unit::getFR() {
  return _FR;
}

void Unit::initialize() {
  _dir = randDir();
  _handle = 0;
  _cells = 0;
  _currentCell = 0;
  _FR = 0;
  _millis = 0;
}

void Unit::setCurrentCell(int currentCell) {
   _currentCell = currentCell;
}

void Unit::setFR(long frameRate) {
   _FR = frameRate;
}

void Unit::toggleDir() {
  _dir = -1 * _dir;
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
