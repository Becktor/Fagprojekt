#include <Arduino.h>
#include "Tiles.h"

//Returns whether the tile is solid.
boolean getSolid(byte tile) {
  return tile == ROCK;
}

//Returns whether the tile is solid from above.
boolean getPlatform(byte tile) {
  return tile == PLATFORM;
}
