#include <Arduino.h>
#include "Tiles.h"

boolean getSolid(Tiles tile) {
  return SOLID[tile];
}
