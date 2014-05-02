#include <Arduino.h>
#include "Tiles.h"
#include "Geo.h"
#include "Module.h"
#include "Scene.h"
#include "SceneGenerator.h"

void newScene(Scene *scene, Point *entrance, Point *exit) {
  clearScene(scene);
  Modules modules[XMODULES][YMODULES];
  modulate(modules, entrance, exit);
  generate(scene, modules, entrance, exit);
  shell(scene);
}

void clearScene(Scene *scene) {
  for(int i = 0; i < SCENE_WIDTH; i++)
    for(int j = 0; j < SCENE_HEIGHT; j++)
      scene->setTile(i, j, NONE);
}

//Note that the dimensions are switched in the TYPETILE arrays, because of how the arrays are structured visually in the code.
void fillModule(Scene *scene, Modules module, int dX, int dY, boolean portalRoom, boolean entrance, Point *portal) {
  byte (*tiles)[MODULE_WIDTH][MODULE_HEIGHT];
  getModuleTiles(module, &tiles);
  for(int i = 0; i < MODULE_WIDTH; i++) {
    for(int j = 0; j < MODULE_HEIGHT; j++) {
      Tiles tile;
      byte tileData = (*tiles)[j][i];
      int x = dX + i, y = dY + j;
      if(tileData == TILE_PORTAL) {
        if(portalRoom) {
          if(entrance)
            tile = ENTRANCE;
          else
            tile = EXIT;
          portal->setPoint(x, y);
        } else
          tile = NONE;
      } else
        tile = (Tiles) tileData;
      if(scene->getTile(x, y) == NULL || scene->getTile(x, y) < tile) //Prioritises tiles depending on their enum value (none is lowest).
        scene->setTile(x, y, tile);
    }
  }
}

void generate(Scene *scene, Modules modules[XMODULES][YMODULES], Point *entrance, Point *exit) {
  for(int i = 0; i < XMODULES; i++) {
    for(int j = 0; j < YMODULES; j++) {
      boolean isPortalRoom, isEntrance;
      Point *portal;
      if(entrance->getX() == i && entrance->getY() == j) {
        isPortalRoom = true;
        isEntrance = true;
        portal = entrance;
      } else if(exit->getX() == i && exit->getY() == j) {
        isPortalRoom = true;
        isEntrance = false;
        portal = exit;
      } else
        isPortalRoom = false;
      fillModule(scene, modules[i][j], i * MODULE_WIDTH - i, j * MODULE_HEIGHT - j, isPortalRoom, isEntrance, portal);
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
