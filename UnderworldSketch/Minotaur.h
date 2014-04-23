#ifndef minotaur_h
#define minotaur_h

#include "Logic.h"

#define SPEED 1
#define HEIGHT 40
#define WIDTH 30

class Minotaur : public Unit {
  public:
    Minotaur(int x, int y);
    void updateAI(int dTime, Logic *logic);
};
#endif
