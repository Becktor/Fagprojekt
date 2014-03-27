#include "Tiles.h"
#include "Unit.h"
#include "Scene.h"
#include "Logic.h"

Logic::Logic(Scene *scene) {
  setMap(scene);
}

void Logic::moveUnit(Unit unit) {
  
}

void Logic::setMap(Scene *scene) {
  _scene = scene;
}
