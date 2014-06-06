#include <Arduino.h>
#include "Tiles.h"
#include "Prop.h"
#include "Unit.h"
#include "Minotaur.h"
#include "Scene.h"

char worldToGrid(int x) {
  if(x < 0)
    return (x + 1) / TILE_SIZE - 1;
  else
    return x / TILE_SIZE;
}

int gridToWorld(char x) {
  return x * TILE_SIZE;
}

Scene::Scene() {
  _props = LinkedList<Prop*>();
  _units = LinkedList<Unit*>();
  _minoIndex = 0;
  for(int i = 0; i < MINOTAURS; i++)
    _minotaurs[i] = new Minotaur();
}

void Scene::addMinotaur(char x, char y) {
  if(_minoIndex != MINOTAURS) {
    addUnit(_minotaurs[_minoIndex], x, y);
    _minotaurs[_minoIndex]->fillHealth();
    _minoIndex++;
  }
}

void Scene::addProp(Prop *prop, char x, char y) {
  moveProp(prop, x, y);
  _props.add(prop);
}

//Adds the given unit to the units list and sets it at the given tile.
void Scene::addUnit(Unit *unit, char x, char y) {
  moveProp(unit, x, y);
  _units.add(unit);
}

void Scene::clearUnits() {
  _units.clear();
  _minoIndex = 0;
}

boolean Scene::contains(char x, char y) {
  return x >= 0 && x < SCENE_WIDTH && y >= 0 && y < SCENE_HEIGHT;
}

byte Scene::getWidth() {
  return SCENE_WIDTH;
}

byte Scene::getHeight() {
  return SCENE_HEIGHT;
}

//Returns the tile at the grid coordinates
byte Scene::getTile(char x, char y) {
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

void Scene::moveProp(Prop* prop, char x, char y) {
  Rect *hitbox = &(prop->_hitbox);
  hitbox->setPos(x * TILE_SIZE + (TILE_SIZE - hitbox->_width) / 2, y * TILE_SIZE + TILE_SIZE - hitbox->_height);
}

void Scene::setTile(char x, char y, byte tile) {
  if(contains(x, y))
    _tiles[x][y] = tile;
}
