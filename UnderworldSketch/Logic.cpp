#include <Arduino.h>
#include "Tiles.h"
#include "Direction.h"
#include "Geo.h"
#include "Unit.h"
#include "Scene.h"
#include "Logic.h"

Logic::Logic(Scene *scene) {
  _scene = scene;
  restartGame();
}

void Logic::restartGame() {
  _gameOver = false;
  _heroWin = false;
}

boolean Logic::isGameOver() {
  return _gameOver;
}

boolean Logic::isHeroWin() {
  return _heroWin;
}

void Logic::gravitate(Unit *unit, int dTime) { //Unused dTime
  unit->setYVel(GRAVITY + unit->getYVel());
}

boolean Logic::isGrounded(Unit *unit) {
  Rect *hitbox = unit->getHitbox();
  int xStart = hitbox->getX() / TILE_SIZE,
      xEnd = (hitbox->getX() + hitbox->getWidth() - 1) / TILE_SIZE,
      y = (hitbox->getY() + hitbox->getHeight()) / TILE_SIZE;
  for(int i = xStart; i <= xEnd; i++) {
    Tiles tile = _scene->getTile(i, y);
    if(getSolid(tile) || getPlatform(tile))
      return true;
  }
  return false;
}

boolean Logic::isSolid(int x, int y) {
  return getSolid(_scene->getTile(x / TILE_SIZE, y / TILE_SIZE));
}

//Returns whether the movement was complete (true) or partial (false)
boolean Logic::moveUnitHoriz(Unit *unit, int dX) {
  Rect *hitbox = unit->getHitbox();
  int x, y = hitbox->getY();
  Direction dir;
  if(dX < 0) {
    x = hitbox->getX();
    dir = LEFT;
  } else if(dX > 0) {
    x = hitbox->getX() + hitbox->getWidth() - 1;
    dir = RIGHT;
  } else
    return true;
  int tileXStart = x / TILE_SIZE + dir,
      tileXEnd = (x + dX) / TILE_SIZE,
      tileYStart = y / TILE_SIZE,
      tileYEnd = (y + hitbox->getHeight() - 1) / TILE_SIZE;
  if(x < 0)
    tileXStart--;
  if(x + dX < 0)
    tileXEnd--;
  if(y < 0)
    tileYStart--;
  if(y + hitbox->getHeight() - 1 < 0)
    tileYEnd--;

  for(int tileX = tileXStart; dir * tileX <= dir * tileXEnd; tileX += dir) {
    for(int tileY = tileYStart; tileY <= tileYEnd; tileY++) {
      Tiles tile = _scene->getTile(tileX, tileY);
      if(getSolid(tile)) {
        if(dir == LEFT)
          unit->translate((tileX + 1) * TILE_SIZE - x, 0);
        else
          unit->translate(tileX * TILE_SIZE - x - 1, 0);
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
    dir = UP;
  } else if(dY > 0) {
    y = hitbox->getY() + hitbox->getHeight() - 1;
    dir = DOWN;
  } else
    return true;
  int tileXStart = x / TILE_SIZE,
      tileXEnd = (x + hitbox->getWidth() - 1) / TILE_SIZE,
      tileYStart = y / TILE_SIZE + dir,
      tileYEnd = (y + dY) / TILE_SIZE;
  if(x < 0)
    tileXStart--;
  if(x + hitbox->getWidth() - 1 < 0)
    tileXEnd--;
  if(y < 0)
    tileYStart--;
  if(y + dY < 0)
    tileYEnd--;

  for(int tileX = tileXStart; tileX <= tileXEnd; tileX++) {
    for(int tileY = tileYStart; dir * tileY <= dir * tileYEnd; tileY += dir) {
      Tiles tile = _scene->getTile(tileX, tileY);
      if(getSolid(tile) || (getPlatform(tile) && dir == DOWN)) {
        if(dir == UP)
          unit->translate(0, (tileY + 1) * TILE_SIZE - y);
        else
          unit->translate(0, tileY * TILE_SIZE - y - 1);
        return false;
      }
    }
  }
  unit->translate(0, dY);
  return true;
}

void Logic::setGameOver(boolean gameOver) {
  _gameOver = gameOver;
}
