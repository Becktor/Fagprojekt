#include <Arduino.h>
#include "Tiles.h"
#include "Geo.h"
#include "Module.h"
#include "Scene.h"
#include "SceneGenerator.h"

//Ensure that the object is not deconstructed for leaving the scope.
void newScene(Scene *scene) {
  Modules modules[XMODULES][YMODULES];
  Point entrance = Point(), exit = Point();
  modulate(modules, &entrance, &exit);
  generate(scene, modules, &entrance, &exit);
  shell(scene);
}

void generate(Scene *scene, Modules modules[XMODULES][YMODULES], Point *entrance, Point *exit) {
  for(int i = 0; i < XMODULES; i++) {
    for(int j = 0; j < YMODULES; j++) {
      fillModule(scene, modules[i][j], i * MODULE_WIDTH - i, j * MODULE_HEIGHT - j);
    }
  }
}

//Note that the dimensions are switched in the TYPETILE arrays, because of how the arrays are structured visually in the code.
void fillModule(Scene *scene, Modules module, int dX, int dY) {
  byte (*tiles)[MODULE_WIDTH][MODULE_HEIGHT];
  getModuleTiles(module, &tiles);
  for(int i = 0; i < MODULE_WIDTH; i++) {
    for(int j = 0; j < MODULE_HEIGHT; j++) {
      Tiles tile = (Tiles) (*tiles)[j][i];
      int x = dX + i, y = dY + j;
      if(scene->getTile(x, y) < tile) //Prioritises tiles depending on their enum value (none is lowest).
        scene->setTile(x, y, tile);
    }
  }
}

void modulate(Modules modules[XMODULES][YMODULES], Point *entrance, Point *exit) {
  short x = random(XMODULES), y = YMODULES - 1;
  modules[x][y] = TYPE1;
  entrance->setPoint(x, y);
  while(true) {
    short r;
    if(x == 0)
      r = random(0, 4);
    else if(x == XMODULES - 1)
      r = random(-3, 1);
    else
      r = random(-3, 4);
    if(r < 0) {
      x--;
      if(modules[x][y] != TYPE3)
        modules[x][y] = TYPE1;
    } else if(r > 0) {
      x++;
      if(modules[x][y] != TYPE3)
        modules[x][y] = TYPE1;   
    } else {
      if(y == 0) {
        exit->setPoint(x, y);
        return;
      }
      if(modules[x][y] == TYPE1)
        modules[x][y] = TYPE2;
      else
        modules[x][y] = TYPE4;
      y--;
      modules[x][y] = TYPE3;
    }
  }
}

void shell(Scene *scene) {
  for(int i = 0; i < SCENE_WIDTH; i++) {
    scene->setTile(i, 0, ROCK);
    scene->setTile(i, SCENE_HEIGHT - 1, ROCK);
  }
  for(int i = 0; i < SCENE_HEIGHT; i++) {
    scene->setTile(0, i, ROCK);
    scene->setTile(SCENE_WIDTH - 1, i, ROCK);
  }
}
