#include <Arduino.h>
#include "Tiles.h"
#include "Direction.h"
#include "Geo.h"
#include "Unit.h"
#include "Scene.h"
#include "Logic.h"

Logic::Logic(Scene *scene) {
  setMap(scene);
}

void Logic::gravitate(Unit *unit, int dTime) { //Unused dTime
  unit->setYVel(GRAVITY + unit->getYVel());
}

//Returns whether the movement was complete (true) or partial (false)
boolean Logic::moveUnitHoriz(Unit *unit, int dX) {
  Rect *hitbox = unit->getHitbox();
  int x, y = hitbox->getY();
  Direction dir;
  if(dX < 0) {
    x = hitbox->getX();
    dir = Left;
  } else if(dX > 0) {
    x = hitbox->getX() + hitbox->getWidth() - 1;
    dir = Right;
  } else
    return true;
  int tileXStart = x / TILE_SIZE,
      tileXEnd = (x + dX) / TILE_SIZE,
      tileYStart = y / TILE_SIZE,
      tileYEnd = (y + hitbox->getHeight() - 1) / TILE_SIZE,
      tileX = tileXStart,
      tileY = tileYStart;
  for(;dir * tileX <= dir * tileXEnd; tileX += dir) {
    for(;tileY <= tileYEnd; tileY++) {
      if(_scene->tileIsSolid(tileX, tileY)) {
        if(dir == Left)
          unit->translate((tileX + 1) * TILE_SIZE - x, 0);
        else
          unit->translate(tileX * TILE_SIZE - hitbox->getWidth() - x, 0);
        return false;
      }
    }
  }
  unit->translate(dX, 0);
  return true;
}

//Returns whether the movement was complete (true) or partial (false)
boolean Logic::moveUnitVerti(Unit *unit, int dY) {
  Rect *hitbox = unit->getHitbox();
  int x = hitbox->getX(), y;
  Direction dir;
  if(dY < 0) {
    y = hitbox->getY();
    dir = Up;
  } else if(dY > 0) {
    y = hitbox->getY() + hitbox->getHeight() - 1;
    dir = Down;
  } else
    return true;
  int tileXStart = x / TILE_SIZE,
      tileXEnd = (x + hitbox->getWidth() - 1) / TILE_SIZE,
      tileYStart = y / TILE_SIZE,
      tileYEnd = (y + dY) / TILE_SIZE,
      tileX = tileXStart,
      tileY = tileYStart;

  for(;tileX <= tileXEnd; tileX++) {
    for(;dir * tileY <= dir * tileYEnd; tileY += dir) {
      if(_scene->tileIsSolid(tileX, tileY)) {
        if(dir == Up)
          unit->translate(0, (tileY + 1) * TILE_SIZE - y);
        else
          unit->translate(0, tileY * TILE_SIZE - hitbox->getHeight() - y);
        return false;
      }
    }
  }
  unit->translate(0, dY);
  return true;
}

void Logic::setMap(Scene *scene) {
  _scene = scene;
}
