#ifndef modules_h
#define modules_h

#include <Arduino.h>
#include "Tiles.h";

#define MODULE_WIDTH 5
#define MODULE_HEIGHT 5

enum Modules{
  TYPE0 = 0, //Closed room
  TYPE1 = 1, //Exit left & right
  TYPE2 = 2, //Exit left, right & up
  TYPE3 = 3, //Exit left, right & down
  TYPE4 = 4  //Exit left, right, up & down
};

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

/*  4x4 tiles
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
#endif
