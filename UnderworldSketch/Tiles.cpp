#include <Arduino.h>
#include "Tiles.h"

//Returns whether the tile is solid.
boolean getSolid(Tiles tile) {
  return tile == ROCK;
}

//Returns whether the tile is solid from above.
boolean getPlatform(Tiles tile) {
  return tile == PLATFORM || tile == LADDER_TOP;
}

//Returns whether the tile is a ladder.
boolean getLadder(Tiles tile) {
  return tile == LADDER || tile == LADDER_TOP;
}
