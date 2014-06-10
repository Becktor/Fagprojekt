#include <Arduino.h>
#include "Tiles.h"
#include "Geo.h"
#include "Prop.h"
#include "Unit.h"
#include "Minotaur.h"
#include "Coin.h"
#include "Scene.h"

char worldToGrid(int x) {
  if(x < 0)
    return (x + 1) / TILE_SIZE - 1;
  else
    return x / TILE_SIZE;
}

int gridToWorld(byte x) {
  return x * TILE_SIZE;
}

Scene::Scene() {
  _props = LinkedList<Prop*>();
  _units = LinkedList<Unit*>();
  _minoIndex = 0;
  _coinIndex = 0;
  for(int i = 0; i < MINOTAURS; i++)
    _minotaurs[i] = new Minotaur();
  for(int i = 0; i < COINS; i++)
    _coins[i] = new Coin();
}

void Scene::addCoin(byte x, byte y) {
  if(_coinIndex != COINS) {
    addProp(_coins[_coinIndex], x, y);
    _coinIndex++;
  }
}
void Scene::addMinotaur(byte x, byte y) {
  if(_minoIndex != MINOTAURS) {
    addUnit(_minotaurs[_minoIndex], x, y);
    _minotaurs[_minoIndex]->fillHealth();
    _minoIndex++;
  }
}

void Scene::addProp(Prop *prop, byte x, byte y) {
  moveProp(prop, x, y);
  _props.add(prop);
}


//Adds the given unit to the units list and sets it at the given tile.
void Scene::addUnit(Unit *unit, byte x, byte y) {
  moveProp(unit, x, y);
  _units.add(unit);
}

void Scene::clearUnits() {
  _units.clear();
  _minoIndex = 0;
}

boolean Scene::contains(byte x, byte y) {
  return x < SCENE_WIDTH && y < SCENE_HEIGHT;
}

byte Scene::getWidth() {
  return SCENE_WIDTH;
}

byte Scene::getHeight() {
  return SCENE_HEIGHT;
}

//Returns the tile at the grid coordinates
byte Scene::getTile(byte x, byte y) {
  if(contains(x, y))
    return _tiles[x][y];
  else
    return ROCK;
}

LinkedList<Unit*>* Scene::getUnits() {
  return &_units;
}

LinkedList<Prop*>* Scene::getProps() {
  return &_props;
}

void Scene::moveProp(Prop* prop, byte x, byte y) {
  Rect *hitbox = &(prop->_hitbox);
  hitbox->_x = x * TILE_SIZE + (TILE_SIZE - hitbox->_width) / 2;
  hitbox->_y = y * TILE_SIZE + TILE_SIZE - hitbox->_height;
}

void Scene::setTile(byte x, byte y, byte tile) {
  if(contains(x, y))
    _tiles[x][y] = tile;
}
