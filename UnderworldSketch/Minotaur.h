#ifndef minotaur_h
#define minotaur_h

#include "Logic.h"

const static short
    MINO_SPEED = 1,
    MINO_HEIGHT = 40,
    MINO_WIDTH = 30;

class Minotaur : public Unit {
  public:
    Minotaur(int x, int y);
    void updateAI(int dTime, Logic *logic);
};
#endif
