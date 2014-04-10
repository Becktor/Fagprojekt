#ifndef hero_h
#define hero_h

#include "Direction.h"
#include "Logic.h"

#define HEIGHT_STAND 20 //Height stand value
#define HEIGHT_DUCK 10 //Duck height
#define WIDTH 10
#define SPEED_JUMP 2
#define SPEED_WALK 1
#define SPEED_RUNNING 3

class Hero : public Unit {
  public:
    Hero(int x, int y);
    void updateAI(int dTime, Logic *logic);
};
#endif
