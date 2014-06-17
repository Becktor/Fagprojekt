#ifndef coin_h
#define coin_h

#include "Prop.h"

const static byte
    COIN_FRICTION = 1,
    COIN_SCORE = 50;

const static word
    COIN_FR = 100,
    COIN_INV_TIME = 10000;

class Coin : public Prop {
  public:
    Coin();
    void collideX();
    void collideY();
    void hit(byte damage, char force);
    void initialize();
};
#endif

