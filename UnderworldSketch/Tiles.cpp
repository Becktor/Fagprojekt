#include <Arduino.h>
#include "Tiles.h"

//Returns whether the tile is solid.
boolean getSolid(byte tile) {
  return tile == ROCK;
}

//Returns whether the tile is solid from above.
boolean getPlatform(byte tile) {
  return tile == PLATFORM || tile == LADDER_TOP;
}

//Returns whether the tile is a ladder.
boolean getLadder(byte tile) {
  return tile == LADDER || tile == LADDER_TOP;
}
