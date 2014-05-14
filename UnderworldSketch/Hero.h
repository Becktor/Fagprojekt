#ifndef hero_h
#define hero_h

#include "Direction.h"
#include "Logic.h"
#include <Wire.h>
#include <ArduinoNunchuk.h>

const static byte
    HERO_HEALTH = 3,
    HERO_DAMAGE = 1,
    HERO_RANGE = 50,
    HERO_HEIGHT_STAND = 45, //Height stand value
    HERO_HEIGHT_DUCK = 20, //Duck height
    HERO_WIDTH = 42,
    HERO_SPEED_JUMP = 15,
    HERO_SPEED_WALK = 1,
    HERO_SPEED_RUN = 5;

class Hero : public Unit {
  private:
    ArduinoNunchuk *_nunchuk;
    boolean _attack, _duck, _jump, _attackSound;

  public:
    Hero(int x, int y, ArduinoNunchuk* nunchuk);
    void updateAI(int dTime, Logic *logic);
    boolean getAttackSound();
};

#endif

