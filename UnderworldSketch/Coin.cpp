#include "Coin.h"
#include "Prop.h"
#include "Sprites.h"

Coin::Coin() : Prop(COINS_WIDTH, COINS_HEIGHT, COINS_WIDTH) { 
  updateHandle(COINS_HANDLE, COINS_CELLS);
  _FR = COIN_FR;
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
  accelerate(COIN_FRICTION, 0);
}
