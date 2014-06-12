#include "Geo.h"
#include "Prop.h"
#include "Direction.h"

Prop::Prop(byte width, byte height, byte imageWidth) : _hitbox(width, height) {
  _levitate = false;
  _imageWidth = imageWidth;
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
  _aniTime = 0;
  _wait = false;
}

void Prop::newHandle(byte handle, byte cells, byte FR) {
  if(!_wait && (_handle != handle || _FR != FR)) {
    _handle = handle;
    _cells = cells;
    _currentCell = 0;
    _FR = FR;
    _aniTime = 0;
  }
}

void Prop::updateAnimation(byte dTime) {
  _aniTime += dTime;
  //while(_aniTime >= _FR) {
  if(_aniTime >= _FR) {
    //_aniTime -= _FR;
    _aniTime = 0;
    if(_currentCell == _cells - 1) {
      _wait = false;
      _currentCell = 0; 
    }
    else
      _currentCell++; 
  }
}

//Returns either target or a value numerically closer to target
//compared to current equal to change.
char Prop::zoomIn(byte zoom, char current, char target) {
  if(target > current)
    return min(current + zoom, target);
  else
    return max(current - zoom, target);
}
