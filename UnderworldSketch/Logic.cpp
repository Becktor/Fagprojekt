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

void Logic::addAttack(int x, int y, int width, int height, int damage, Prop *owner) {
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

Prop* Logic::getHero() {
  return _hero;
}

boolean Logic::isGameOver() {
  return _gameOver;
}

boolean Logic::isGrounded(Prop *prop) {
  Rect *hitbox = prop->getHitbox();
  int y = hitbox->getY() + hitbox->getHeight();
  char yTile = worldToGrid(y);
  if(yTile != worldToGrid(y - 1)) {
    char xStartTile = worldToGrid(hitbox->getX()),
         xEndTile = worldToGrid(hitbox->getX() + hitbox->getWidth() - 1);
    for(char i = xStartTile; i <= xEndTile; i++) {
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
  return getSolid(_scene->getTile(worldToGrid(x), worldToGrid(y)));
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
  char tileXStart = worldToGrid(x) + dir,
       tileXEnd = worldToGrid(x + dX),
       tileYStart = worldToGrid(y),
       tileYEnd = worldToGrid(y + hitbox->getHeight() - 1);
  for(char tileX = tileXStart; dir * tileX <= dir * tileXEnd; tileX += dir) {
    for(char tileY = tileYStart; tileY <= tileYEnd; tileY++) {
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
  char tileXStart = worldToGrid(x),
       tileXEnd = worldToGrid(x + hitbox->getWidth() - 1),
       tileYStart = worldToGrid(y) + dir,
       tileYEnd = worldToGrid(y + dY);
  for(char tileX = tileXStart; tileX <= tileXEnd; tileX++) {
    for(char tileY = tileYStart; dir * tileY <= dir * tileYEnd; tileY += dir) {
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

void Logic::setHero(Prop *hero) {
  _hero = hero;
}
