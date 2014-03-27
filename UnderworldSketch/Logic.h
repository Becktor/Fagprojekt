#ifndef logic_h
#define logic_h

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
    void moveUnit(Unit unit);
    void setMap(Scene *scene);
};

#endif
