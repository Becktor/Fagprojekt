#ifndef minotaur_h
#define minotaur_h

#include "Logic.h"

const static byte
    MINO_HEALTH = 3,
    MINO_WSPEED = 3,
    MINO_RSPEED = 2,
    MINO_HEIGHT = 48,
    MINO_WIDTH = 56,
    MINO_WALKING = 0,
    MINO_WALKING_CELLS = 7,
    MINO_RUNNING = 1,
    MINO_RUNNING_CELLS = 1;

class Minotaur : public Unit {
  public:
    Minotaur();
    void fillHealth();
    void updateAI(int dTime, Logic *logic);
};
#endif

