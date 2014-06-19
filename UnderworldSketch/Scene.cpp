#include <Arduino.h>
#include "Tiles.h"
#include "Geo.h"
#include "Prop.h"
#include "Unit.h"
#include "Minotaur.h"
#include "Coin.h"
#include "Scene.h"

//Converts a given world coordinate to grid (tile) coordinate
char worldToGrid(int x) {
  if(x < 0)
    return (x + 1) / TILE_SIZE - 1;
  else
    return x / TILE_SIZE;
}

//Converts a given tile coordinate to world coordinate.
int gridToWorld(byte x) {
  return x * TILE_SIZE;
}

Scene::Scene() {
  _coinList = LinkedList<Coin*>();
  _unitList = LinkedList<Unit*>();
  _minoIndex = 0;
  _coinIndex = 0;
  //Instantiate all used props.
  for(byte i = 0; i < MINOTAURS; i++)
    _minotaurs[i] = new Minotaur();
  for(byte i = 0; i < COINS; i++)
    _coins[i] = new Coin();
}

//Add a coin to the given tile.
void Scene::addCoin(byte x, byte y) {
  if(_coinIndex != COINS) {
    Coin *coin = _coins[_coinIndex];
    setProp(coin, x, y);
    _coinList.add(coin);
    _coinIndex++;
  }
}

//Add a minotaur to the given tile.
void Scene::addMinotaur(byte x, byte y) {
  if(_minoIndex != MINOTAURS) {
    addUnit(_minotaurs[_minoIndex], x, y);
    _minoIndex++;
  }
}

//Add a unit to the given tile.
void Scene::addUnit(Unit* unit, byte x, byte y) {
  setProp(unit, x, y);
  _unitList.add(unit);
}

//Clears all props.
void Scene::clearProps() {
  _unitList.clear();
  _coinList.clear();
  _minoIndex = 0;
  _coinIndex = 0;
}

//Returns whether the given tile is within the scene.
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
//Returns rock outside the map.
byte Scene::getTile(byte x, byte y) {
  if(contains(x, y))
    return _tiles[x][y];
  else
    return ROCK;
}

//Sets the given prop to the given tile.
//and initializes.
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
