#ifndef tiles_h
#define tiles_h

#include <Arduino.h>

enum Tiles{
  N = 0, //None
  P = 1, //Platform
  R = 2, //Rock
  L = 3, //Ladder
  A = 4  //Ladder platform
};

static const boolean SOLID[5] = {false, false, true, false, false};
boolean getSolid(Tiles tile);
boolean getPlatform(Tiles tile);
boolean getLadder(Tiles tile);
#endif
