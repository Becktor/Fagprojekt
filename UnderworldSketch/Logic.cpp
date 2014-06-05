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

void Logic::addAttack(Attack* attack) {
  _attacks.add(attack);
}

boolean Logic::atExit(Prop *prop) {
  Rect *hitbox = prop->getHitbox();
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
    Rect *area = attack->_area;
    for(int j = 0; j < units->size(); j++) {
      Unit *unit = units->get(j);
      Rect *hitbox = unit->getHitbox();
      if(unit != attack->_owner && hitbox->contains(area)) {
        unit->damage(attack->_damage);
        unit->setXVel(attack->_force);
      }
    }
  }
  _attacks.clear();
}

Prop* Logic::getHero() {
  return _hero;
}

void Logic::gravitate(Prop *prop, int dTime) { //Unused dTime
  prop->setYVel(GRAVITY + prop->getYVel());
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

//Returns whether the movement was complete (true) or partial (false)
boolean Logic::movePropHoriz(Prop *prop, int dX) {
  Rect *hitbox = prop->getHitbox();
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
  Rect *hitbox = prop->getHitbox();
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
  if(!prop->getLevitate())
    gravitate(prop, dTime);
  if(!movePropHoriz(prop, prop->getXVel()))
    prop->setXVel(0);
  if(!movePropVerti(prop, prop->getYVel()))
    prop->setYVel(0);
}
