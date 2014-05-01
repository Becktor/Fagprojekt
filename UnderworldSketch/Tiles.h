#ifndef tiles_h
#define tiles_h

#include <Arduino.h>

enum Tiles{
  NONE = 0,
  PLATFORM = 1,
  ROCK = 2,
  LADDER = 3,
  LADDER_TOP = 4
};

boolean getSolid(Tiles tile);
boolean getPlatform(Tiles tile);
boolean getLadder(Tiles tile);
#endif
