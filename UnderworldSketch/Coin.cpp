#include "Coin.h"
#include "Prop.h"

Coin::Coin() : Prop(COIN_WIDTH, COIN_HEIGHT) { }

void Coin::hit(byte damage, char force) {
  setXVel(force);
  setYVel(-abs(force) / 2);
}
