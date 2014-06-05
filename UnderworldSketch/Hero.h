#ifndef hero_h
#define hero_h

#include "Geo.h"
#include "Direction.h"
#include "Logic.h"
#include "Attack.h"
#include <Wire.h>
#include <ArduinoNunchuk.h>

const static byte
    HERO_ATT_DAMAGE = 1,
    HERO_ATT_FORCE = 7,
    HERO_ATT_RANGE = 50,
    HERO_HEALTH = 3,
    HERO_HEIGHT_STAND = 45, //Height stand value
    HERO_HEIGHT_DUCK = 20, //Duck height
    HERO_WIDTH = 42,
    HERO_SPEED_JUMP = 15,
    HERO_SPEED_WALK = 1,
    HERO_SPEED_RUN = 5;

class Hero : public Unit {
  private:
    Rect _attackArea;
    Attack _attack;
    ArduinoNunchuk *_nunchuk;
    boolean _isAttacking, _isDucking, _isJumping, _attackSound;
  public:
    Hero(ArduinoNunchuk* nunchuk);
    void updateAI(int dTime, Logic *logic);
    boolean getAttackSound();
};
#endif
