#include <Arduino.h>
#include "Direction.h"
#include "Tiles.h"
#include "Geo.h"
#include "Module.h"
#include "Scene.h"
#include "Minotaur.h"
#include "SceneGenerator.h"

void newScene(Scene *scene, Point *entrance, Point *exit, byte difficulty) {
  //Init
  for(byte i = 0; i < SCENE_WIDTH; i++)
    for(byte j = 0; j < SCENE_HEIGHT; j++)
      scene->setTile(i, j, NONE);
  scene->clearProps();
  byte modules[XMODULES][YMODULES];
  boolean enemies[XMODULES][YMODULES];
  for(byte i = 0; i < XMODULES; i++) {
    for(byte j = 0; j < YMODULES; j++) {
      modules[i][j] = NONE;
      enemies[i][j] = false;
    }
  }
  //New map
  modulate(modules, entrance, exit);
  //Avoid spawning enemies in portal rooms.
  enemies[entrance->_x][entrance->_y] = true;
  enemies[exit->_x][exit->_y] = true;
  byte enemyAmount = min(difficulty, MINOTAURS);
  while(enemyAmount != 0) {
    byte r = random(XMODULES * YMODULES),
         x = r % XMODULES,
         y = r / XMODULES;
    if(!enemies[x][y]) {
      enemies[x][y] = true;
      enemyAmount--;
    }
  }
  generate(scene, modules, enemies, entrance, exit);
}

//Note that the dimensions are switched in the TYPETILE arrays, because of how the arrays are structured visually in the code.
void fillModule(Scene *scene, byte module, byte dX, byte dY, boolean portalRoom, boolean entrance, Point *portal, boolean enemy) {
  byte (*tiles)[MODULE_WIDTH][MODULE_HEIGHT];
  getModuleTiles(module, &tiles);
  for(byte i = 0; i < MODULE_WIDTH; i++) {
    for(byte j = 0; j < MODULE_HEIGHT; j++) {
      byte tile = (*tiles)[j][i], x = dX + i, y = dY + j;
      if(tile == TILE_OBJECT) {
        if(portalRoom) {
          if(entrance)
            tile = START;
          else
            tile = END;
          portal->setPoint(x, y);
        } else {
          tile = NONE;
          if(enemy) {
            scene->addMinotaur(x, y);
            scene->addCoin(x,y);
          }
        }
      }
      if(scene->getTile(x, y) == NULL || scene->getTile(x, y) < tile) //Prioritises tiles depending on their enum value (none is lowest).
        scene->setTile(x, y, tile);
    }
  }
}

void generate(Scene *scene, byte modules[XMODULES][YMODULES], boolean enemies[XMODULES][YMODULES], Point *entrance, Point *exit) {
  boolean hasEntrance = false, hasExit = false;
  for(byte i = 0; i < XMODULES; i++) {
    for(byte j = 0; j < YMODULES; j++) {
      boolean isPortalRoom = false, isEntrance = false;
      Point *portal;
      if(!hasEntrance && entrance->_x == i && entrance->_y == j) {
        isPortalRoom = true;
        isEntrance = true;
        portal = entrance;
        hasEntrance = true;
      } else if(!hasExit && exit->_x == i && exit->_y == j) {
        isPortalRoom = true;
        isEntrance = false;
        portal = exit;
        hasExit = true;
      }
      fillModule(scene, modules[i][j], i * MODULE_WIDTH - i - 1, j * MODULE_HEIGHT - j - 1, isPortalRoom, isEntrance, portal, enemies[i][j]);
    }
  }
}

void modulate(byte modules[XMODULES][YMODULES], Point *entrance, Point *exit) {
  byte x = random(XMODULES), y = YMODULES - 1;
  char dir = randDir();
  modules[x][y] = TYPE1;
  entrance->setPoint(x, y);
  for(;;) {
    byte r = random(5), newX = x + dir;
    if(r == 4 || newX >= XMODULES) {
      if(y == 0) {
        exit->setPoint(x, y);
        return;
      } else {
        modules[x][y]++; //TYPE1 becomes TYPE2, TYPE3 becomes TYPE4, no other possibilities.
        y--;
        modules[x][y] = TYPE3;
        if(r == 4)
          dir = randDir();
        else
          dir = -1 * dir;
      }
    } else {
      x = newX;
      modules[x][y] = TYPE1;
    }
  }
}
