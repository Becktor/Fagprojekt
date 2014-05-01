#ifndef modules_h
#define modules_h

#include <Arduino.h>
#include "Tiles.h";

const static int
    TYPE0_MODULES = 1,
    TYPE1_MODULES = 2,
    TYPE2_MODULES = 1,
    TYPE3_MODULES = 1,
    TYPE4_MODULES = 1,
    MODULE_WIDTH = 5,
    MODULE_HEIGHT = 5;

enum Modules{
  TYPE0 = 0, //Closed room
  TYPE1 = 1, //Exit left & right
  TYPE2 = 2, //Exit left, right & up
  TYPE3 = 3, //Exit left, right & down
  TYPE4 = 4  //Exit left, right, up & down
};

static Tiles
TYPE0_TILES[TYPE0_MODULES][MODULE_WIDTH][MODULE_HEIGHT] = {
  {
    {R, R, R, R, R},
    {R, N, N, N, R},
    {R, N, N, N, R},
    {R, N, N, N, R},
    {R, R, R, R, R}
  }
},
TYPE1_TILES[TYPE1_MODULES][MODULE_WIDTH][MODULE_HEIGHT] = {
  {
    {R, R, R, R, R},
    {N, N, N, N, N},
    {N, N, N, N, N},
    {N, N, N, N, N},
    {R, R, R, R, R}
  },
  {
    {R, R, R, R, R},
    {N, N, N, N, N},
    {N, N, P, N, N},
    {N, N, N, N, N},
    {R, R, R, R, R}
  }
},
TYPE2_TILES[TYPE2_MODULES][MODULE_WIDTH][MODULE_HEIGHT] = {
  {
    {R, N, N, N, R},
    {N, N, N, N, N},
    {N, N, N, N, N},
    {N, N, N, N, N},
    {R, R, R, R, R}
  }
},
TYPE3_TILES[TYPE3_MODULES][MODULE_WIDTH][MODULE_HEIGHT] = {
  {
    {R, R, R, R, R},
    {N, N, N, N, N},
    {N, N, N, N, N},
    {N, N, N, N, N},
    {R, N, N, N, R}
  }
},
TYPE4_TILES[TYPE4_MODULES][MODULE_WIDTH][MODULE_HEIGHT] = {
  {
    {R, N, N, N, R},
    {N, N, N, N, N},
    {N, N, N, N, N},
    {N, N, N, N, N},
    {R, N, N, N, R}
  }
};

/*
//5x5 tiles
static Tiles
TYPE00TILE[MODULE_WIDTH][MODULE_HEIGHT] = {
  {R, R, R, R, R},
  {R, N, N, N, R},
  {R, N, N, N, R},
  {R, N, N, N, R},
  {R, R, R, R, R}
},
TYPE10TILE[MODULE_WIDTH][MODULE_HEIGHT] = {
  {R, R, R, R, R},
  {N, N, N, N, N},
  {N, N, P, N, N},
  {N, N, N, N, N},
  {R, R, R, R, R}
},
TYPE20TILE[MODULE_WIDTH][MODULE_HEIGHT] = {
  {R, N, N, N, R},
  {N, N, N, N, N},
  {N, P, P, P, N},
  {N, N, N, N, N},
  {R, R, R, R, R}
},
TYPE30TILE[MODULE_WIDTH][MODULE_HEIGHT] = {
  {R, R, R, R, R},
  {N, N, N, N, N},
  {N, P, P, P, N},
  {N, N, N, N, N},
  {R, N, N, N, R}
},
TYPE40TILE[MODULE_WIDTH][MODULE_HEIGHT] = {
  {R, N, N, N, R},
  {N, N, N, N, N},
  {N, N, P, N, N},
  {N, N, N, N, N},
  {R, N, N, N, R}
};

//4x4 tiles
static Tiles
TYPE00TILE[MODULE_WIDTH][MODULE_HEIGHT] = {
  {R, R, R, R},
  {R, N, N, R},
  {R, N, N, R},
  {R, R, R, R}
},
TYPE10TILE[MODULE_WIDTH][MODULE_HEIGHT] = {
  {R, R, R, R},
  {N, N, N, N},
  {N, N, N, N},
  {R, R, R, R}
},
TYPE20TILE[MODULE_WIDTH][MODULE_HEIGHT] = {
  {R, N, N, R},
  {N, N, N, N},
  {N, N, N, N},
  {R, R, R, R}
},
TYPE30TILE[MODULE_WIDTH][MODULE_HEIGHT] = {
  {R, R, R, R},
  {N, N, N, N},
  {N, N, N, N},
  {R, N, N, R}
},
TYPE40TILE[MODULE_WIDTH][MODULE_HEIGHT] = {
  {R, N, N, R},
  {N, N, N, N},
  {N, N, N, N},
  {R, N, N, R}
};
*/

void getModuleTiles(Modules module, Tiles (**tiles)[MODULE_WIDTH][MODULE_HEIGHT]);


#endif
