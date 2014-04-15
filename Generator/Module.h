#ifndef modules_h
#define modules_h

#include <Arduino.h>
#include "Tiles.h";

#define MODULE_WIDTH 4
#define MODULE_HEIGHT 4

enum Modules{
  TYPE0 = 0, //Closed room
  TYPE1 = 1, //Exit left & right
  TYPE2 = 2, //Exit left, right & up
  TYPE3 = 3, //Exit left, right & down
  TYPE4 = 4  //Exit left, right, up & down
};

static Tiles
TYPE00TILE[MODULE_WIDTH][MODULE_HEIGHT] = {
  {R, R, R, R},
  {R, N, N, R},
  {R, N, N, R},
  {R, R, R, R}
},
TYPE10TILE[4][4] = {
  {R, R, R, R},
  {N, N, N, N},
  {N, N, N, N},
  {R, R, R, R}
},
TYPE20TILE[4][4] = {
  {R, N, N, R},
  {N, N, N, N},
  {N, N, N, N},
  {R, R, R, R}
},
TYPE30TILE[4][4] = {
  {R, R, R, R},
  {N, N, N, N},
  {N, N, N, N},
  {R, N, N, R}
},
TYPE40TILE[4][4] = {
  {R, N, N, R},
  {N, N, N, N},
  {N, N, N, N},
  {R, N, N, R}
};
#endif
