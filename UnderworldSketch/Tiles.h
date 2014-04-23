#ifndef tiles_h
#define tiles_h

#include <Arduino.h>

enum Tiles{
  N = 0, //None
  R = 1, //Rock
  W = 2  //Wall
};

static const boolean SOLID[3] = {false, true, true};
boolean getSolid(Tiles tile);
#endif
