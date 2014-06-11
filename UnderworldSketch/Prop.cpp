#include "Geo.h"
#include "Prop.h"
#include "Direction.h"

Prop::Prop(byte width, byte height, byte imageWidth) : _hitbox(width, height) {
  _levitate = false;
  _imageWidth = imageWidth;
  initialize();
}

void Prop::checkFrameChange(long milis) {
  if((milis - _millis) > _FR)
  {   
   _millis = milis;
   if(_currentCell == _cells - 1)
    _currentCell = 0; 
   else
    _currentCell++; 
  }
}

void Prop::collideX() { }

void Prop::collideY() { }

void Prop::hit(byte damage, char force) {
  _xVel += force;
  _yVel -= abs(force);
}

void Prop::initialize() {
  _dir = randDir();
  _xVel = 0;
  _yVel = 0;
  _handle = 0;
  _cells = 0;
  _currentCell = 0;
  _FR = 0;
  _millis = 0;
}

void Prop::updateHandle(byte handle, byte cells, byte FR) {
  if(_handle != handle) {
    _handle = handle;
    _cells = cells;
    _FR = FR;
    _currentCell = 0;
  }
}

//Returns either target or a value numerically closer to target
//compared to current equal to change.
char Prop::zoomIn(byte zoom, char current, char target) {
  if(target > current)
    return min(current + zoom, target);
  else if(target < current)
    return max(current - zoom, target);
}
