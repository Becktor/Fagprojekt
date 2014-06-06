#include "Coin.h"
#include "Prop.h"

Coin::Coin() : Prop(COIN_WIDTH, COIN_HEIGHT) { }

void Coin::hit(byte damage, char force) {
  _xVel += force;
  _yVel -= abs(force);
}

void Coin::xCollide() {
  if(COIN_FRICTION > abs(_xVel))
    _xVel = 0;
  else
    _xVel = COIN_FRICTION - _xVel;
}

void Coin::yCollide() {
  if(COIN_FRICTION > abs(_yVel))
    _yVel = 0;
  else
    _yVel = COIN_FRICTION - _yVel;
  if(_xVel > COIN_FRICTION)
    _xVel -= COIN_FRICTION;
  else if(_xVel < -COIN_FRICTION)
    _xVel += COIN_FRICTION;
  else
    _xVel = 0;
}
