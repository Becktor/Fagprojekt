#ifndef coin_h
#define coin_h

#include "Prop.h"

const static byte
    COIN_HEIGHT = 10,
    COIN_WIDTH = 10;

class Coin : public Prop {
  public:
    Coin();
    void hit(byte damage, char force);
};
#endif

