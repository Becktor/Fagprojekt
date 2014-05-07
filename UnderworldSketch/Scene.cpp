#include <Arduino.h>
#include "Tiles.h"
#include "Scene.h"
#include "Unit.h"

Scene::Scene() {
  _units = LinkedList<Unit*>();
  _props = LinkedList<Prop*>();
}

//Adds the given unit to the units list and sets it at the given tile.
void Scene::addUnit(Unit *unit, Point *point) {
  Rect *hitbox = unit->getHitbox();
  Point *pos = hitbox->getPos();
  pos->setPoint(point->getX() * TILE_SIZE + (TILE_SIZE - hitbox->getWidth()) / 2, point->getY() * TILE_SIZE + TILE_SIZE - hitbox->getHeight());
  _units.add(unit);
}
void Scene::addProp(Prop *prop, Point *point) {
  Rect *hitbox = prop->getHitbox();
  Point *pos = hitbox->getPos();
  pos->setPoint(point->getX() * TILE_SIZE + (TILE_SIZE - hitbox->getWidth()) / 2, point->getY() * TILE_SIZE + TILE_SIZE - hitbox->getHeight());
  _props.add(prop);
}

void Scene::clearUnits() {
  _units.clear();
}

boolean Scene::contains(int x, int y) {
  return x >= 0 && x < SCENE_WIDTH && y >= 0 && y < SCENE_HEIGHT;
}

int Scene::getWidth() {
  return SCENE_WIDTH;
}

int Scene::getHeight() {
  return SCENE_HEIGHT;
}

Tiles Scene::getTile(int x, int y) {
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
void Scene::setTile(int x, int y, Tiles tile) {
  if(contains(x, y))
    _tiles[x][y] = tile;
}
