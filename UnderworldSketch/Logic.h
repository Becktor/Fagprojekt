#ifndef logic_h
#define logic_h

#include "Scene.h"
#include "Unit.h"

class Unit;
class Logic
{
  private:
    Scene _scene;
  public:
    Logic();
    Logic(Scene scene);
    void moveUnit(Unit unit);
    void setScene(Scene scene);
};

#endif
