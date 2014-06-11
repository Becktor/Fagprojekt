#ifndef coin_h
#define coin_h

#include "Prop.h"

const static byte
    COIN_FRICTION = 1,
    COIN_FR = 100;
class Coin : public Prop {
  public:
    Coin();
    void xCollide();
    void yCollide();
};
#endif

