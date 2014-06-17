#include "Coin.h"
#include "Prop.h"
#include "Sprites.h"

Coin::Coin() : Prop(COIN_WIDTH, COIN_HEIGHT, COIN_WIDTH, COIN_HEIGHT, COIN_INV_TIME) { }

void Coin::collideX() {
  _xVel = -zoomIn(COIN_FRICTION, _xVel, 0);
}

void Coin::collideY() {
  _yVel = -zoomIn(COIN_FRICTION, _yVel, 0);
  _xVel = zoomIn(COIN_FRICTION, _xVel, 0);
}

void Coin::hit(byte damage, char force) {
  Prop::hit(damage, force);
  push(force);
}
