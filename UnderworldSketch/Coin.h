#ifndef coin_h
#define coin_h

#include "Prop.h"

const static byte
    COIN_FRICTION = 1,
    COIN_FR = 100,
    COIN_SCORE = 10;
class Coin : public Prop {
  public:
    Coin();
    void collideX();
    void collideY();
    void initialize();
};
#endif

