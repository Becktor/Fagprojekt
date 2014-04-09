#include <Arduino.h>
#include "Tiles.h"
#include "Scene.h"

Scene generate() { }

void shell(Scene *scene) {
  for(int i = 0; i < SCENE_WIDTH; i++) {
    scene->setTile(i, 0, Rock);
    scene->setTile(i, SCENE_HEIGHT - 1, Rock);
  }
  for(int i = 1; i < SCENE_HEIGHT - 1; i++) {
    scene->setTile(0, i, Rock);
    scene->setTile(SCENE_WIDTH - 1, i, Rock);
  }
}
