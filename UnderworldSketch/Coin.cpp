#include "Coin.h"
#include "Prop.h"
#include "Sprites.h"

Coin::Coin() : Prop(COIN_WIDTH, COIN_HEIGHT, COIN_WIDTH) { }

void Coin::initialize() {
  Prop::initialize();
  updateHandle(COIN_HANDLE, COIN_CELLS, _FR = COIN_FR);
}

void Coin::collideX() {
  _xVel = -zoomIn(COIN_FRICTION, _xVel, 0);
}

void Coin::collideY() {
  _yVel = -zoomIn(COIN_FRICTION, _yVel, 0);
  _xVel = zoomIn(COIN_FRICTION, _xVel, 0);
}
