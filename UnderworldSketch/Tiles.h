#ifndef tiles_h
#define tiles_h

#include <Arduino.h>

enum Tiles{
  Rock = 0,
  Spikes = 1,
  Wall = 2
};

const static boolean _solid[] = {true, true, true};
boolean getSolid(Tiles tile);
#endif
