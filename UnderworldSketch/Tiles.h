#ifndef tiles_h
#define tiles_h

#include <Arduino.h>

enum Tiles {
  NONE = 0,
  PLATFORM = 1,
  ROCK = 2,
  START = 3,
  END = 4
};

boolean getSolid(byte tile);
boolean getPlatform(byte tile);
#endif
