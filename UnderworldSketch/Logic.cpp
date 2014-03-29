#include <Arduino.h>
#include "Direction.h"
#include "Tiles.h"
#include "Geo.h"
#include "Unit.h"
#include "Scene.h"
#include "Logic.h"

Logic::Logic(Scene *scene) {
  setMap(scene);
}

//Returns whether the movement was complete (true) or partial (false)
boolean Logic::moveUnitHoriz(Unit *unit, int dX) {
  Rect hitbox = (*unit).getHitbox();
  int x, y = hitbox.getY();
  Direction dir = (*unit).getDir();
  if(dir == Left)
    x = hitbox.getX();
  else
    x = hitbox.getX() + hitbox.getWidth() - 1;
  int tileXStart = x / TILE_SIZE,
      tileXEnd = (x + dX) / TILE_SIZE,
      tileYStart = y / TILE_SIZE,
      tileYEnd = (y + hitbox.getHeight() - 1) / TILE_SIZE,
      tileX = tileXStart,
      tileY = tileYStart;
  for(;dir * tileX <= dir * tileXEnd; tileX += dir) {
    for(;tileY <= tileYEnd; tileY++) {
      if(!(*_scene).tileIsSolid(tileX, tileY)) {
        //partial move code!
        (*unit).toggleDir();
        return false;
      }
    }
  }
  (*unit).translate(dX, 0);
  return true;
}

void Logic::setMap(Scene *scene) {
  _scene = scene;
}
