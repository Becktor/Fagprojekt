#ifndef tiles_h
#define tiles_h

#include <Arduino.h>

enum Tiles{
  NONE = 0,
  PLATFORM = 1,
  ROCK = 2,
  LADDER = 3,
  LADDER_TOP = 4,
  ENTRANCE = 5,
  EXIT = 6
};

boolean getSolid(byte tile);
boolean getPlatform(byte tile);
boolean getLadder(byte tile);
#endif
