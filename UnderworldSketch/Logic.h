#ifndef logic_h
#define logic_h

#include <Arduino.h>
#include "Tiles.h"
#include "Unit.h"
#include "Scene.h"

#define GRAVITY 1

class Unit;
class Logic
{
  private:
    Scene *_scene;
  public:
    Logic(Scene *scene);
    void gravitate(Unit *unit, int dTime);
    boolean moveUnitHoriz(Unit *unit, int dX);
    boolean moveUnitVerti(Unit *unit, int dY);
    void setMap(Scene *scene);
};
#endif
