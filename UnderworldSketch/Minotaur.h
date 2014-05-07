#ifndef minotaur_h
#define minotaur_h

#include "Logic.h"

const static short
    MINO_SPEED = 3,
    MINO_HEIGHT = 42,
    MINO_WIDTH = 42;

class Minotaur : public Unit {
  public:
    Minotaur(int x, int y);
    void updateAI(int dTime, Logic *logic);
};
#endif
