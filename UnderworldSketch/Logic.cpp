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
}

void Logic::addAttack(Attack* attack) {
  _attacks.add(attack);
}

boolean Logic::atExit(Prop *prop) {
  Rect* hitbox = &(prop->_hitbox);
  char tileXEnd = worldToGrid(hitbox->getX() + hitbox->getWidth() - 1),
       tileYEnd = worldToGrid(hitbox->getY() + hitbox->getHeight() - 1);
  for(char tileX = worldToGrid(hitbox->getX()); tileX <= tileXEnd; tileX++) {
    for(char tileY = worldToGrid(hitbox->getY()); tileY <= tileYEnd; tileY++) {
      if(EXIT == _scene->getTile(tileX, tileY))
        return true;
    }
  }
  return false;
}

void Logic::clearAttacks() {
  _attacks.clear();
}

void Logic::coinCol() {
  LinkedList<Prop*> *props = _scene->getProps();
    for(int j = 0; j < props->size(); j++) {
      Prop *prop = props->get(j);
      Rect *hitboxC = &(prop->_hitbox);
      Rect *hitboxH = &(getHero()->_hitbox);
      if(hitboxH->contains(hitboxC)) {
        //add bonus
        //&getHero->&_score=getHero->&(_score + 100);
    }
  }
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

void Logic::gravitate(Prop *prop, int dTime) { //Unused dTime
  prop->_yVel += GRAVITY;
}

boolean Logic::isGameOver() {
  return _gameOver;
}

boolean Logic::isGrounded(Prop *prop) {
  Rect *hitbox = &(prop->_hitbox);
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

//Returns whether the movement was complete (true) or partial (false)
boolean Logic::movePropHoriz(Prop *prop, int dX) {
  Rect *hitbox = &(prop->_hitbox);
  int x = hitbox->getX(), y = hitbox->getY();
  Direction dir;
  if(dX < 0) {
    dir = LEFT;
  } else if(dX > 0) {
    x += hitbox->getWidth() - 1;
    dir = RIGHT;
  } else
    return true;
  char tileXEnd = worldToGrid(x + dX),
       tileYEnd = worldToGrid(y + hitbox->getHeight() - 1);
  for(char tileX = worldToGrid(x) + dir; dir * tileX <= dir * tileXEnd; tileX += dir) {
    for(char tileY = worldToGrid(y); tileY <= tileYEnd; tileY++) {
      byte tile = _scene->getTile(tileX, tileY);
      if(getSolid(tile)) {
        if(dir == LEFT)
          prop->translate(gridToWorld(tileX + 1) - x, 0);
        else
          prop->translate(gridToWorld(tileX) - x - 1, 0);
        return false;
      }
    }
  }
  prop->translate(dX, 0);
  return true;
}

//Returns whether the movement was complete (true) or partial (false)
boolean Logic::movePropVerti(Prop *prop, int dY) {
  Rect *hitbox = &(prop->_hitbox);
  int x = hitbox->getX(), y = hitbox->getY();
  Direction dir;
  if(dY < 0)
    dir = UP;
  else if(dY > 0) {
    y += hitbox->getHeight() - 1;
    dir = DOWN;
  } else
    return true;
  char tileXEnd = worldToGrid(x + hitbox->getWidth() - 1),
       tileYEnd = worldToGrid(y + dY);
  for(char tileX = worldToGrid(x); tileX <= tileXEnd; tileX++) {
    for(char tileY = worldToGrid(y) + dir; dir * tileY <= dir * tileYEnd; tileY += dir) {
      byte tile = _scene->getTile(tileX, tileY);
      if(getSolid(tile) || (getPlatform(tile) && dir == DOWN)) {
        if(dir == UP)
          prop->translate(0, gridToWorld(tileY + 1) - y);
        else
          prop->translate(0, gridToWorld(tileY) - y - 1);
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

void Logic::updatePhysics(Prop* prop, int dTime) {
  if(!prop->_levitate)
    gravitate(prop, dTime);
  if(!movePropHoriz(prop, prop->_xVel))
    prop->_xVel = 0;
  if(!movePropVerti(prop, prop->_yVel))
    prop->_yVel = 0;
}
