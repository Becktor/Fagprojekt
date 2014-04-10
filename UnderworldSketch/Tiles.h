#ifndef tiles_h
#define tiles_h

#include <Arduino.h>

enum Tiles{
  Rock = 0,
  Spikes = 1,
  Wall = 2
};

static const PROGMEM boolean SOLID[3] = {true, true, true};
boolean getSolid(Tiles tile);
#endif
