#ifndef tiles_h
#define tiles_h

#include <Arduino.h>

enum Tiles{
  Void = 0,
  Rock = 1,
  Spikes = 2,
  Wall = 3
};

static const PROGMEM boolean SOLID[4] = {false, true, true, true};
boolean getSolid(Tiles tile);
#endif
