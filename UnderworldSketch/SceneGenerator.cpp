#include <Arduino.h>
#include "Tiles.h"
#include "Scene.h"
#include "SceneGenerator.h"

//Ensure that the object is not deconstructed for leaving the scope.
Scene generate() {
  Scene scene = Scene();
  shell(&scene);
  return scene;
}

void shell(Scene *scene) {
  for(int i = 0; i < SCENE_WIDTH; i++) {
    scene->setTile(i, 0, Wall);
    scene->setTile(i, SCENE_HEIGHT - 1, Wall);
  }
  for(int i = 0; i < SCENE_HEIGHT; i++) {
    scene->setTile(0, i, Wall);
    scene->setTile(SCENE_WIDTH - 1, i, Wall);
  }
}
