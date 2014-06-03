#ifndef minotaur_h
#define minotaur_h

#include "Logic.h"
#include "Unit.h"

const static byte
    MINO_HEALTH = 3,
    MINO_WSPEED = 3,
    MINO_RSPEED = 5,
    MINO_HEIGHT = 42,
    MINO_WIDTH = 42,
    MINO_WALKING = 0,
    MINO_WALKING_CELLS = 7,
    MINO_RUNNING = 8,
    MINO_RUNNING_CELLS = 3;

class Minotaur : public Unit {
  public:
    Minotaur(int x, int y);
    Minotaur();
    void updateAI(int dTime, Logic *logic);
};

#endif

