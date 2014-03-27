#include <Arduino.h>
#include "Tiles.h"
#include "Scene.h"

Scene::Scene() { }

int Scene::getWidth() {
  return SCENE_WIDTH;
}

int Scene::getHeight() {
  return SCENE_HEIGHT;
}

boolean Scene::tileIsSolid(int x, int y) {
  getSolid(_tiles[x][y]);
}

void Scene::setTile(int x, int y, Tiles tile) {
  _tiles[x][y] = tile;
}
