#ifndef minotaur_h
#define minotaur_h

#include "Logic.h"

const static short
    COIN_HEIGHT = 20,
    COIN_WIDTH = 20;

class Coin : public Unit {
  public:
    Coin(int x, int y);
};
#endif
