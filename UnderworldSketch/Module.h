#ifndef modules_h
#define modules_h

#include <Arduino.h>

const static byte  
    TYPE0_MODULES = 1,
    TYPE1_MODULES = 2,
    TYPE2_MODULES = 1,
    TYPE3_MODULES = 1,
    TYPE4_MODULES = 1,
    MODULE_WIDTH = 5,
    MODULE_HEIGHT = 5,
    TILE_OBJECT = 7;

enum Modules{
  TYPE0 = 0, //Closed room
  TYPE1 = 1, //Exit left & right
  TYPE2 = 2, //Exit left, right & up
  TYPE3 = 3, //Exit left, right & down
  TYPE4 = 4  //Exit left, right, up & down
};

static byte
TYPE0_TILES[TYPE0_MODULES][MODULE_WIDTH][MODULE_HEIGHT] = {
  {
    {2, 2, 2, 2, 2},
    {2, 0, 0, 0, 2},
    {0, 0, 0, 0, 0},
    {0, 0, 7, 0, 2},
    {2, 2, 2, 2, 2}
  }
},
TYPE1_TILES[TYPE1_MODULES][MODULE_WIDTH][MODULE_HEIGHT] = {
  {
    {2, 2, 2, 2, 2},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 7, 0, 0},
    {2, 2, 2, 2, 2}
  },
  {
    {2, 2, 2, 2, 2},
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 7, 0, 0},
    {2, 2, 2, 2, 2}
  }
},
TYPE2_TILES[TYPE2_MODULES][MODULE_WIDTH][MODULE_HEIGHT] = {
  {
    {2, 0, 1, 0, 2},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1},
    {0, 0, 7, 0, 0},
    {2, 2, 2, 2, 2}
  }
},
TYPE3_TILES[TYPE3_MODULES][MODULE_WIDTH][MODULE_HEIGHT] = {
  {
    {2, 0, 0, 2, 2},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 7, 0, 0},
    {2, 0, 1, 0, 2}
  }
},
TYPE4_TILES[TYPE4_MODULES][MODULE_WIDTH][MODULE_HEIGHT] = {
  {
    {2, 0, 1, 0, 2},
    {0, 7, 0, 0, 0},
    {1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {2, 0, 1, 0, 2}
  }
};

void getModuleTiles(byte module, byte (**tiles)[MODULE_WIDTH][MODULE_HEIGHT]);
#endif
