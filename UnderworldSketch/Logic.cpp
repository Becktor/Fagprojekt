#include <Arduino.h>
#include <LinkedList.h>
#include "Tiles.h"
#include "Direction.h"
#include "Geo.h"
#include "Prop.h"
#include "Attack.h"
#include "Scene.h"
#include "Logic.h"

Logic::Logic(Scene *scene) {
  _scene = scene;
  restartGame();
  _score = 0;
}

void Logic::addAttack(Attack* attack) {
  _attacks.add(attack);
}

boolean Logic::atExit(Prop *prop) {
  Rect* hitbox = &(prop->_hitbox);
  char tileXEnd = worldToGrid(hitbox->_x + hitbox->_width - 1),
       tileYEnd = worldToGrid(hitbox->_y + hitbox->_height - 1);
  for(char tileX = worldToGrid(hitbox->_x); tileX <= tileXEnd; tileX++) {
    for(char tileY = worldToGrid(hitbox->_y); tileY <= tileYEnd; tileY++) {
      if(EXIT == _scene->getTile(tileX, tileY))
        return true;
    }
  }
  return false;
}

void Logic::clearAttacks() {
  _attacks.clear();
}

boolean Logic::coinCol(Prop* prop) {
  Rect *hitboxC = &(prop->_hitbox);
  Rect *hitboxH = &(getHero()->_hitbox);
    if(hitboxH->contains(hitboxC)) {
      //add bonus
      _score += 10;
      return true;
    }
  return false;
}

void Logic::executeAttacks(Prop* prop) {
  Rect *hitbox = &(prop->_hitbox);
  for(int i = 0; i < _attacks.size(); i++) {
    Attack *attack = _attacks.get(i);
    Rect *area = attack->_area;
    if(prop != attack->_owner && hitbox->contains(area))
      prop->hit(attack->_damage, attack->_force);
  }
}

Prop* Logic::getHero() {
  return _hero;
}

boolean Logic::isGameOver() {
  return _gameOver;
}

boolean Logic::isGrounded(Prop *prop) {
  Rect *hitbox = &(prop->_hitbox);
  int y = hitbox->_y + hitbox->_height;
  char yTile = worldToGrid(y);
  if(yTile != worldToGrid(y - 1)) {
    char xStartTile = worldToGrid(hitbox->_x),
         xEndTile = worldToGrid(hitbox->_x + hitbox->_width - 1);
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

//Returns whether the movement was complete (true) or partial (false)
boolean Logic::movePropHoriz(Prop *prop, int dX) {
  Rect *hitbox = &(prop->_hitbox);
  int x = hitbox->_x, y = hitbox->_y;
  Direction dir;
  if(dX < 0) {
    dir = LEFT;
  } else if(dX > 0) {
    x += hitbox->_width - 1;
    dir = RIGHT;
  } else
    return true;
  char tileXEnd = worldToGrid(x + dX),
       tileYEnd = worldToGrid(y + hitbox->_height - 1);
  for(char tileX = worldToGrid(x) + dir; dir * tileX <= dir * tileXEnd; tileX += dir) {
    for(char tileY = worldToGrid(y); tileY <= tileYEnd; tileY++) {
      byte tile = _scene->getTile(tileX, tileY);
      if(getSolid(tile)) {
        if(dir == LEFT)
          hitbox->_x += gridToWorld(tileX + 1) - x;
        else
          hitbox->_x += gridToWorld(tileX) - x - 1;
        return false;
      }
    }
  }
  hitbox->_x += dX;
  return true;
}

//Returns whether the movement was complete (true) or partial (false)
boolean Logic::movePropVerti(Prop *prop, int dY) {
  Rect *hitbox = &(prop->_hitbox);
  int x = hitbox->_x, y = hitbox->_y;
  Direction dir;
  if(dY < 0)
    dir = UP;
  else if(dY > 0) {
    y += hitbox->_height - 1;
    dir = DOWN;
  } else
    return true;
  char tileXEnd = worldToGrid(x + hitbox->_width - 1),
       tileYEnd = worldToGrid(y + dY);
  for(char tileX = worldToGrid(x); tileX <= tileXEnd; tileX++) {
    for(char tileY = worldToGrid(y) + dir; dir * tileY <= dir * tileYEnd; tileY += dir) {
      byte tile = _scene->getTile(tileX, tileY);
      if(getSolid(tile) || (getPlatform(tile) && dir == DOWN)) {
        if(dir == UP)
          hitbox->_y += gridToWorld(tileY + 1) - y;
        else
          hitbox->_y += gridToWorld(tileY) - y - 1;
        return false;
      }
    }
  }
  hitbox->_y += dY;
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

void Logic::updatePhysics(Prop* prop, int dTime) {
  if(!movePropHoriz(prop, prop->_xVel))
    prop->xCollide();
  if(!movePropVerti(prop, prop->_yVel + GRAVITY))
    prop->yCollide();
  else if(!prop->_levitate)
    prop->_yVel += GRAVITY;
}
