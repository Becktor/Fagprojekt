#ifndef logic_h
#define logic_h

#include <Arduino.h>
#include "Tiles.h"
#include "Unit.h"
#include "Scene.h"

class Unit;
class Logic
{
  private:
    Scene *_scene;
  public:
    Logic(Scene *scene);
    boolean moveUnitHoriz(Unit *unit, int x);
    void setMap(Scene *scene);
};
#endif
