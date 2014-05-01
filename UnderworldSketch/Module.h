#ifndef modules_h
#define modules_h

#include <Arduino.h>
#include "Tiles.h";

const static byte
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

static byte
TYPE0_TILES[TYPE0_MODULES][MODULE_WIDTH][MODULE_HEIGHT] = {
  {
    {2, 2, 2, 2, 2},
    {2, 0, 0, 0, 2},
    {2, 0, 0, 0, 2},
    {2, 0, 0, 0, 2},
    {2, 2, 2, 2, 2}
  }
},
TYPE1_TILES[TYPE1_MODULES][MODULE_WIDTH][MODULE_HEIGHT] = {
  {
    {2, 2, 2, 2, 2},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {2, 2, 2, 2, 2}
  },
  {
    {2, 2, 2, 2, 2},
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0},
    {2, 2, 2, 2, 2}
  }
},
TYPE2_TILES[TYPE2_MODULES][MODULE_WIDTH][MODULE_HEIGHT] = {
  {
    {2, 0, 0, 0, 2},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {2, 2, 2, 2, 2}
  }
},
TYPE3_TILES[TYPE3_MODULES][MODULE_WIDTH][MODULE_HEIGHT] = {
  {
    {2, 2, 2, 2, 2},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {2, 0, 0, 0, 2}
  }
},
TYPE4_TILES[TYPE4_MODULES][MODULE_WIDTH][MODULE_HEIGHT] = {
  {
    {2, 0, 0, 0, 2},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {2, 0, 0, 0, 2}
  }
};

/*
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
*/
void getModuleTiles(Modules module, byte (**tiles)[MODULE_WIDTH][MODULE_HEIGHT]);

#endif
