#include "Coin.h"
#include "Prop.h"
#include "Sprites.h"

Coin::Coin() : Prop(COIN_WIDTH, COIN_HEIGHT, COIN_WIDTH, COIN_HEIGHT, COIN_INV_TIME) { }

//Horizontal collision function.
//Called when colliding in the x-axis
void Coin::collideX() {
  _xVel = -zoomIn(COIN_FRICTION, _xVel, 0);
}

//Vertical collision function.
//Called when colliding in the y-axis
void Coin::collideY() {
  _yVel = -zoomIn(COIN_FRICTION, _yVel, 0);
  _xVel = zoomIn(COIN_FRICTION, _xVel, 0);
}

//Hit function.
//Called when attacked, if not invulnerable.
void Coin::hit(byte damage, char force) {
  Prop::hit(damage, force);
  push(force);
}

//Initialize function.
//Called when used in a new map.
void Coin::initialize() {
  Prop::initialize();
  newHandle(COIN_HANDLE, COIN_CELLS, COIN_FR);  
}
