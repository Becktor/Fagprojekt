#include <Arduino.h>
#include "Module.h"

//Given a module type and a module pointer, it changes the pointer value to the given module.
void getModuleTiles(byte module, byte (**tiles)[MODULE_WIDTH][MODULE_HEIGHT]) {
  if(module == TYPE1)
    *tiles = &TYPE1_TILES[random(TYPE1_MODULES)];
  else if(module == TYPE2)
    *tiles = &TYPE2_TILES[random(TYPE2_MODULES)];
  else if(module == TYPE3)
    *tiles = &TYPE3_TILES[random(TYPE3_MODULES)];
  else if(module == TYPE4)
    *tiles = &TYPE4_TILES[random(TYPE4_MODULES)];
  else
    *tiles = &TYPE0_TILES[random(TYPE0_MODULES)];
}

