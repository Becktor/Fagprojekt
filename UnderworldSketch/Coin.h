/*
 *  The coin object in the game. Contains a score and functions for physics behavior.
 */

#ifndef coin_h
#define coin_h

#include "Prop.h"

const static byte
    COIN_FRICTION = 1, //Friction and bounciness in one. More is less bouncy.
    COIN_SCORE = 50;

const static word
    COIN_FR = 100, //Miliseconds per animation frame
    COIN_INV_TIME = 500; //Invulnerable time in miliseconds

class Coin : public Prop {
  public:
    Coin();
    void collideX();
    void collideY();
    void hit(byte damage, char force);
    void initialize();
};
#endif

