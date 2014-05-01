#include <Arduino.h>
#include "Tiles.h"
#include "Scene.h"

Scene::Scene() { }

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

void Scene::setTile(int x, int y, Tiles tile) {
  if(contains(x, y))
    _tiles[x][y] = tile;
}
