#include "Geo.h"
#include "Prop.h"
#include "Direction.h"

Prop::Prop(byte width, byte height, byte imageWidth) : _hitbox(width, height) {
  _levitate = false;
  _imageWidth = imageWidth;
  initialize();
}

void Prop::accelerate(byte acc, char targetSpeed) {
  if(targetSpeed > _xVel)
    _xVel = min(_xVel + acc, targetSpeed);
  else if(targetSpeed < _xVel)
    _xVel = max(_xVel - acc, targetSpeed);
}
void Prop::checkFrameChange(long milis) {
  if((milis - _millis) > _FR)
  {   
   _millis = milis;
   if(_currentCell == _cells)
    _currentCell = 0; 
   else
    _currentCell++; 
  }
}

void Prop::updateHandle(byte handle, byte cells) {
  _handle = handle;
  _cells = cells;
  _currentCell = 0;
}

void Prop::hit(byte damage, char force) {
  _xVel += force;
  _yVel -= abs(force);
}

void Prop::initialize() {
  _xVel = 0;
  _yVel = 0;
  _dir = randDir();
  _handle = 0;
  _cells = 0;
  _currentCell = 0;
  _FR = 0;
  _millis = 0;
}

void Prop::xCollide() { }

void Prop::yCollide() { }
