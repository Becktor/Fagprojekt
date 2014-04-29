#include <Arduino.h>
#include "Tiles.h"

//Returns whether the tile is solid.
boolean getSolid(Tiles tile) {
  return SOLID[tile];
}

//Returns whether the tile is solid from above.
boolean getPlatform(Tiles tile) {
  return tile == P;
}

//Returns whether the tile is a ladder.
boolean getLadder(Tiles tile) {
  return tile == L || tile == A;
}
