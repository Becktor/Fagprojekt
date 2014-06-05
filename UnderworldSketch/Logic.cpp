#include <Arduino.h>
#include <LinkedList.h>
#include "Tiles.h"
#include "Direction.h"
#include "Geo.h"
#include "Attack.h"
#include "Scene.h"
#include "Logic.h"

Logic::Logic(Scene *scene) {
  _scene = scene;
  restartGame();
}

void Logic::addAttack(int x, int y, int width, int height, int damage, Unit *owner) {
  Attack attack = Attack(x, y, width, height, damage, owner);
  _attacks.add(&attack);
}

boolean Logic::atExit(Prop *prop) {
  Rect *hitbox = prop->getHitbox();
  int tileXStart = hitbox->getX() / TILE_SIZE,
      tileYStart = hitbox->getY() / TILE_SIZE,
      tileXEnd = (hitbox->getX() + hitbox->getWidth() - 1) / TILE_SIZE,
      tileYEnd = (hitbox->getY() + hitbox->getHeight() - 1) / TILE_SIZE;
  for(int i = tileXStart; i <= tileXEnd; i++) {
    for(int j = tileYStart; j <= tileYEnd; j++) {
      if(EXIT == _scene->getTile(i, j))
        return true;
    }
  }
  return false;
}

void Logic::coinCol() {
  LinkedList<Prop*> *props = _scene->getProps();
    for(int j = 0; j < props->size(); j++) {
      Prop *prop = props->get(j);
      Rect *hitboxC = prop->getHitbox();
      Rect *hitboxH = getHero()->getHitbox();
      if(hitboxH->contains(hitboxC)) {
        //add bonus 
    }
  }
}

void Logic::executeAttacks() {
  LinkedList<Unit*> *units = _scene->getUnits();
  for(int i = 0; i < _attacks.size(); i++) {
    Attack *attack = _attacks.get(i);
    Rect *area = &(attack->_area);
    for(int j = 0; j < units->size(); j++) {
      Unit *unit = units->get(j);
      Rect *hitbox = unit->getHitbox();
      if(unit != attack->_owner && hitbox->contains(area)) {
        unit->damage(attack->_damage);
        unit->setYVel(-10);
      }
    }
  }
  _attacks.clear();
}

Unit* Logic::getHero() {
  return _hero;
}

boolean Logic::isGameOver() {
  return _gameOver;
}

boolean Logic::isGrounded(Prop *prop) {
  Rect *hitbox = prop->getHitbox();
  int y = hitbox->getY() + hitbox->getHeight();
  byte yTile = worldToGrid(y);
  if(yTile != worldToGrid(y - 1)) {
    byte xStartTile = worldToGrid(hitbox->getX()),
         xEndTile = worldToGrid(hitbox->getX() + hitbox->getWidth() - 1);
    for(i = xStartTile; i <= xEndTile; i++) {
      byte tile = _scene->getTile(i, yTile);
      if(getSolid(tile) || getPlatform(tile))
        return true;
    }
  }
  return false;
}

boolean Logic::isHeroWin() {
  return _heroWin;
}

boolean Logic::isSolid(int x, int y) {
  return getSolid(_scene->getTile(x / TILE_SIZE, y / TILE_SIZE));
}


void Logic::gravitate(Unit *unit, int dTime) { //Unused dTime
  unit->setYVel(GRAVITY + unit->getYVel());
}

//Returns whether the movement was complete (true) or partial (false)
boolean Logic::movePropHoriz(Prop *prop, int dX) {
  Rect *hitbox = prop->getHitbox();
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
  if(x < 0) {
    tileXStart--;
    if(x + dX < 0)
      tileXEnd--;
  }
  if(y < 0) {
    tileYStart--;
    if(y + hitbox->getHeight() - 1 < 0)
      tileYEnd--;
  }
  for(int tileX = tileXStart; dir * tileX <= dir * tileXEnd; tileX += dir) {
    for(int tileY = tileYStart; tileY <= tileYEnd; tileY++) {
      byte tile = _scene->getTile(tileX, tileY);
      if(getSolid(tile)) {
        if(dir == LEFT)
          prop->translate((tileX + 1) * TILE_SIZE - x, 0);
        else
          prop->translate(tileX * TILE_SIZE - x - 1, 0);
        return false;
      }
    }
  }
  prop->translate(dX, 0);
  return true;
}

//Returns whether the movement was complete (true) or partial (false)
boolean Logic::movePropVerti(Prop *prop, int dY) {
  Rect *hitbox = prop->getHitbox();
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
  if(x < 0) {
    tileXStart--;
    if(x + hitbox->getWidth() - 1 < 0)
      tileXEnd--;
  }
  if(y < 0) {
    tileYStart--;
    if(y + dY < 0)
      tileYEnd--;
  }
  for(int tileX = tileXStart; tileX <= tileXEnd; tileX++) {
    for(int tileY = tileYStart; dir * tileY <= dir * tileYEnd; tileY += dir) {
      byte tile = _scene->getTile(tileX, tileY);
      if(getSolid(tile) || (getPlatform(tile) && dir == DOWN)) {
        if(dir == UP)
          prop->translate(0, (tileY + 1) * TILE_SIZE - y);
        else
          prop->translate(0, tileY * TILE_SIZE - y - 1);
        return false;
      }
    }
  }
  prop->translate(0, dY);
  return true;
}

void Logic::restartGame() {
  _gameOver = false;
  _heroWin = false;
}

void Logic::setGameOver(boolean gameOver, boolean heroWin) {
  _gameOver = gameOver;
  _heroWin = heroWin;
}

void Logic::setHero(Unit *hero) {
  _hero = hero;
}
