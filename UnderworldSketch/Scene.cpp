#include "Arduino.h"
#include "Scene.h"

Scene::Scene() { }

int Scene::getWidth() {
  return SCENE_WIDTH;
}

int Scene::getHeight() {
  return SCENE_HEIGHT;
}

boolean Scene::isSolid(Point p) {
  return _map[p.getX()][p.getY()];
}

void Scene::setTile(int x, int y, Tiles tile) {
  _map[x][y] = tile;
}

void Scene::setTile(Point p, Tiles tile) {
  setTile(p.getX(), p.getY(), tile);
}
