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
  _coinList = LinkedList<Coin*>();
  _unitList = LinkedList<Unit*>();
  _minoIndex = 0;
  _coinIndex = 0;
  for(byte i = 0; i < MINOTAURS; i++) {
    _minotaurs[i] = new Minotaur();
    //_test[0][i] = _minotaurs[i];
  }
  for(byte i = 0; i < COINS; i++) {
    _coins[i] = new Coin();
    //_test[1][i] = _minotaurs[i];
  }
}

void Scene::addCoin(byte x, byte y) {
  if(_coinIndex != COINS) {
    Coin *coin = _coins[_coinIndex];
    setProp(coin, x, y);
    _coinList.add(coin);
    _coinIndex++;
  }
}

void Scene::addMinotaur(byte x, byte y) {
  if(_minoIndex != MINOTAURS) {
    addUnit(_minotaurs[_minoIndex], x, y);
    _minoIndex++;
  }
}

//Adds the given unit to the units list and sets it at the given tile.
void Scene::addUnit(Unit *unit, byte x, byte y) {
  setProp(unit, x, y);
  _unitList.add(unit);
}

void Scene::clearProps() {
  _unitList.clear();
  _coinList.clear();
  _minoIndex = 0;
  _coinIndex = 0;
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

LinkedList<Coin*>* Scene::getCoins() {
  return &_coinList;
}

LinkedList<Unit*>* Scene::getUnits() {
  return &_unitList;
}

//Returns the tile at the grid coordinates
byte Scene::getTile(byte x, byte y) {
  if(contains(x, y))
    return _tiles[x][y];
  else
    return ROCK;
}

void Scene::setProp(Prop* prop, byte x, byte y) {
  Rect *hitbox = &(prop->_hitbox);
  hitbox->_x = x * TILE_SIZE + (TILE_SIZE - hitbox->_width) / 2;
  hitbox->_y = y * TILE_SIZE + TILE_SIZE - hitbox->_height;
  prop->initialize();
}

void Scene::setTile(byte x, byte y, byte tile) {
  if(contains(x, y))
    _tiles[x][y] = tile;
}
