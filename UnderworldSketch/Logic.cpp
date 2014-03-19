#include "Scene.h"
#include "Unit.h"
#include "Logic.h"

Logic::Logic() {}

Logic::Logic(Scene scene) {
  setScene(scene);
}

void Logic::moveUnit(Unit unit) {
  
}

void Logic::setScene(Scene scene) {
  _scene = scene;
}

