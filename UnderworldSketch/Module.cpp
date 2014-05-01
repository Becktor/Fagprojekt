#include <Arduino.h>
#include "Tiles.h"
#include "Module.h"

void getModuleTiles(Modules module, byte (**tiles)[MODULE_WIDTH][MODULE_HEIGHT]) {
  switch (module) {
    case TYPE0:
      *tiles = &TYPE0_TILES[random(TYPE0_MODULES)];
      return;
    case TYPE1:
      *tiles = &TYPE1_TILES[random(TYPE1_MODULES)];
      return;
    case TYPE2:
      *tiles = &TYPE2_TILES[random(TYPE2_MODULES)];
      return;
    case TYPE3:
      *tiles = &TYPE3_TILES[random(TYPE3_MODULES)];
      return;
    case TYPE4:
      *tiles = &TYPE4_TILES[random(TYPE4_MODULES)];
      return;
  }
}
