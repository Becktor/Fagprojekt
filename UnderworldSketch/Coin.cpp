#include "Coin.h"
#include "Prop.h"

Coin::Coin() : Prop(COIN_WIDTH, COIN_HEIGHT, COIN_IMAGE_WIDTH) { }

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
  accelerate(COIN_FRICTION, 0);
}
