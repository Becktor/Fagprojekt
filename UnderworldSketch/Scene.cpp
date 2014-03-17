#include <Arduino.h>
#include "Scene.h"
#include "Tiles.h"

Scene::Scene() { }

int Scene::getWidth() {
  return SCENE_WIDTH;
}

int Scene::getHeight() {
  return SCENE_HEIGHT;
}

boolean Scene::isSolid(Point p) {
//  return _tiles[p.getX()][p.getY()];
  return false;
}

void Scene::setTile(int x, int y, Tiles tile) {
  //_tiles[x][y] = tile;
}

void Scene::setTile(Point p, Tiles tile) {
  //setTile(p.getX(), p.getY(), tile);
}
