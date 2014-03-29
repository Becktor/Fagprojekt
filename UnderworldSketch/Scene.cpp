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
  if(x >= 0 && x < SCENE_WIDTH && y >= 0 && y < SCENE_HEIGHT)
    getSolid(_tiles[x][y]);
  else
    return true; //By default, the edges of the map is solid.
}

void Scene::setTile(int x, int y, Tiles tile) {
  _tiles[x][y] = tile;
}
