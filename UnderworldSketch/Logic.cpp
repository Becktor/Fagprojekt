#include <Arduino.h>
#include <LinkedList.h>
#include "Tiles.h"
#include "Direction.h"
#include "Geo.h"
#include "Prop.h"
#include "Coin.h"
#include "Attack.h"
#include "Scene.h"
#include "Logic.h"

Logic::Logic(Scene *scene) {
  _scene = scene;
  _gameOver = false;
  _heroWin = false;
}

//Adds the attack to the attack list.
void Logic::addAttack(Attack* attack) {
  _attacks.add(attack);
}

//Returns true if the given prop is at an exit tile.
boolean Logic::atExit(Prop *prop) {
  Rect* hitbox = &(prop->_hitbox);
  byte tileXEnd = worldToGrid(hitbox->_x + hitbox->_width - 1),
       tileYEnd = worldToGrid(hitbox->_y + hitbox->_height - 1);
  for(byte tileX = worldToGrid(hitbox->_x); tileX <= tileXEnd; tileX++) {
    for(byte tileY = worldToGrid(hitbox->_y); tileY <= tileYEnd; tileY++) {
      if(_scene->getTile(tileX, tileY) == END)
        return true;
    }
  }
  return false;
}

//Clears the attack list.
void Logic::clearAttacks() {
  _attacks.clear();
}

//Checks whether the hero collides with the coin.
boolean Logic::coinCollision(Coin* coin) {
  return (_hero->_hitbox).contains(&(coin->_hitbox));
}

//Checks whether any attacks hits the prop.
void Logic::executeAttacks(Prop* prop) {
  Rect *hitbox = &(prop->_hitbox);
  for(byte i = 0; i < _attacks.size(); i++) {
    Attack *attack = _attacks.get(i);
    Rect *area = attack->_area;
    if(prop != attack->_owner && hitbox->contains(area) && !prop->_invulnerable)
      prop->hit(attack->_damage, attack->_force);
  }
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

//Returns whether a given set of world coordinates is walkable.
boolean Logic::isWalkable(int x, int y) {
  byte tile = _scene->getTile(worldToGrid(x), worldToGrid(y));
  return getSolid(tile) || getPlatform(tile);
}

//Returns whether the movement was complete (true) or partial (false)
boolean Logic::movePropHoriz(Prop *prop, int dX) {
  Rect *hitbox = &(prop->_hitbox);
  if(dX == 0)
    return true;
  char dir = getDirection(dX);
  int x = hitbox->side(dir), y = hitbox->_y;
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
  if(dY == 0)
    return true;
  char dir = getDirection(dY);
  int x = hitbox->_x, y = hitbox->surface(dir);
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

//Returns whether the given tile is solid.
boolean Logic::tileIsSolid(byte x, byte y) {
  return getSolid(_scene->getTile(x, y));
}

//Updates the physics for the given prop.
//Moves it according its speed and calls collision functions.
//Also adds the gravity to the velocity.
void Logic::updatePhysics(byte dTime, Prop* prop) {
  if(!movePropHoriz(prop, prop->_xVel))
    prop->collideX();
  if(!movePropVerti(prop, prop->_yVel + GRAVITY))
    prop->collideY();
  else if(!prop->_levitate)
    prop->_yVel += GRAVITY;
}
