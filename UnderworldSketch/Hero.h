#ifndef hero_h
#define hero_h

#include <Wire.h>
#include <ArduinoNunchuk.h>
#include "Geo.h"
#include "Direction.h"
#include "Attack.h"
#include "Logic.h"
#include "Unit.h"

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
    HERO_SPEED_RUN = 5,
    HERO_WALKING_HANDLE = 0,
    HERO_ATTACKING_HANDLE = 1,
    HERO_DUCKING_HANDLE = 2,
    HERO_WALKING_CELLS = 7,
    HERO_ATTACKING_CELLS = 1,
    HERO_DUCKING_CELLS= 1;

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
