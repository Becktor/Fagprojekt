#ifndef minotaur_h
#define minotaur_h

#include "Logic.h"
#include "Unit.h"

const static byte
    MINO_HEALTH = 3,
    MINO_WSPEED = 3,
    MINO_CSPEED = 6,
    MINO_DSPEED = 0,
    MINO_HEIGHT = 72,
    MINO_WIDTH = 80,
    MINO_WALKING = 5,
    MINO_WALKING_CELLS = 3,
    MINO_CHARGING = 3,
    MINO_CHARGING_CELLS = 3,
    MINO_DYING = 4,
    MINO_DYING_CELLS = 3;

class Minotaur : public Unit {
  public:
    Minotaur();
    void fillHealth();
    void updateAI(int dTime, Logic *logic);
    void xCollide();
};
#endif

