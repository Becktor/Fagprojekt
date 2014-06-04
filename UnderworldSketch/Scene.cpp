#include <Arduino.h>
#include "Tiles.h"
#include "Scene.h"
#include "Prop.h"
#include "Unit.h"
#include "Minotaur.h"

Scene::Scene() {
  _props = LinkedList<Prop*>();
  _units = LinkedList<Unit*>();
  _minoIndex = 0;
  for(int i = 0; i < MINOTAURS; i++)
    _minotaurs[i] = new Minotaur();
}

void Scene::addMinotaur(byte x, byte y) {
  if(_minoIndex != MINOTAURS) {
    addUnit(_minotaurs[_minoIndex], x, y);
    _minotaurs[_minoIndex]->fillHealth();
    _minoIndex++;
  }
}

void Scene::addProp(Prop *prop, byte x, byte y) {
  Rect *hitbox = prop->getHitbox();
  hitbox->setPos(x * TILE_SIZE + (TILE_SIZE - hitbox->getWidth()) / 2, y * TILE_SIZE + TILE_SIZE - hitbox->getHeight());
  _props.add(prop);
}

//Adds the given unit to the units list and sets it at the given tile.
void Scene::addUnit(Unit *unit, byte x, byte y) {
  Rect *hitbox = unit->getHitbox();
  hitbox->setPos(x * TILE_SIZE + (TILE_SIZE - hitbox->getWidth()) / 2, y * TILE_SIZE + TILE_SIZE - hitbox->getHeight());
  _units.add(unit);
}

void Scene::clearUnits() {
  _units.clear();
  _minoIndex = 0;
}


boolean Scene::contains(byte x, byte y) {
  return x >= 0 && x < SCENE_WIDTH && y >= 0 && y < SCENE_HEIGHT;
}

byte Scene::getWidth() {
  return SCENE_WIDTH;
}

byte Scene::getHeight() {
  return SCENE_HEIGHT;
}

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
void Scene::setTile(byte x, byte y, byte tile) {
  if(contains(x, y))
    _tiles[x][y] = tile;
}
