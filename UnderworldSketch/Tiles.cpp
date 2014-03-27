#include <Arduino.h>
#include "Tiles.h"

// Currently we store the tile information in arrays in memory. Consider
// using PROGMEM to store in flash instead.

boolean getSolid(Tiles tile) {
  return _solid[tile];
}
