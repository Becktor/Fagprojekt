#ifndef coin_h
#define coin_h

#include "Prop.h"

const static byte
    COIN_HEIGHT = 10,
    COIN_WIDTH = 10;

class Coin : public Prop {
  public:
    Coin(int x, int y);
};
#endif

