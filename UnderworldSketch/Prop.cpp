
#include "Geo.h"
#include "Prop.h"
#include "Direction.h"

Prop::Prop(byte width, byte height, byte imageWidth, byte imageHeight, word invTime) : _hitbox(width, height) {
  _levitate = false;
  _imageWidth = imageWidth;
  _imageHeight = imageHeight;
  _invTime = invTime;
}

//Horizontal collision function.
//Called when colliding in the x-axis
void Prop::collideX() { }

//Vertical collision function.
//Called when colliding in the y-axis
void Prop::collideY() { }

//Hit function.
//Called when attacked, if not invulnerable.
void Prop::hit(byte damage, char force) {
  _invulnerable = true;
  _invTimer = 0;
}

//Initialize function.
//Called when used in a new map.
void Prop::initialize() {
  _dir = randDir();
  _xVel = 0;
  _yVel = 0;
  //_handle = 0;
  //_cells = 0;
  //_FR = 1;
  _currentCell = 0;
  _invTimer = 0;
  _invulnerable = false;
  _animTime = 0;
  _animLock = false;
  _animStop = false;
}

//Changes the current handle, cells and FR, if either the
//handle or FR is not equal to the current.
//Never changes if animLock is true.
void Prop::newHandle(byte handle, byte cells, word FR) {
  if(!_animLock && (_handle != handle || _FR != FR)) {
    _handle = handle;
    _cells = cells;
    _FR = FR;
    _currentCell = 0;
    _animTime = 0;
  }
}

//Short reusable function, that pushes the prop according to the given force.
void Prop::push(char force) {
  _xVel += force;
  _yVel -= abs(force);
}

//Updates the animation frame.
void Prop::updateAnimation(byte dTime) {
  _animTime += dTime;
  while(_animTime >= _FR) {
    _animTime -= _FR;
    if(_currentCell == _cells - 1) {
      if(!_animStop){
        _animLock = false;
        _currentCell = 0; 
      }
    } else
      _currentCell++; 
  }
}

//Updates the time invlunerable, and checks if it should be set to false.
void Prop::updateInvulnerability(byte dTime) {
  if(_invulnerable) {
    _invTimer += dTime;
    if(_invTimer >= _invTime)
      _invulnerable = false;
  }
}

//Returns either target or a value numerically closer to target
//compared to current equal to change.
//Used when accelerating the prop in an axis.
char Prop::zoomIn(byte zoom, char current, char target) {
  if(target > current)
    return min(current + zoom, target);
  else
    return max(current - zoom, target);
}
