#ifndef hero_h
#define hero_h

#include <Wire.h>
#include <ArduinoNunchuk.h>
#include "Geo.h"
#include "Direction.h"
#include "Attack.h"
#include "Logic.h"
#include "Unit.h"
#include "Sprites.h"

const static byte
    HERO_ACC_AIR = 1,
    HERO_ACC_DUCK = 1,
    HERO_ACC_RUN = 2,
    HERO_ACC_WALK = 1,
    HERO_ATT_DAMAGE = 1,
    HERO_ATT_FORCE = 5,
    HERO_ATT_RANGE = 50,
    HERO_HEALTH = 3,
    HERO_HEIGHT_STAND = 45, //Height stand value
    HERO_HEIGHT_DUCK = 36, //Duck height
    HERO_HITBOX_WIDTH = 32,
    HERO_SPEED_JUMP = 15,
    HERO_SPEED_AIR = 2,
    HERO_SPEED_DUCK = 2,
    HERO_SPEED_RUN = 6,
    HERO_SPEED_WALK = 3,
    HERO_WALKING_FR = 200,
    HERO_RUNNING_FR = 100,
    HERO_ATTACKING_FR = 200,
    HERO_DUCKING_FR = 100,
    HERO_IDLE_FR = 200,
    NUNCHUK_MIDDLE = 120,
    NUNCHUK_WALK = 10,
    NUNCHUK_RUN = 40,
    NUNCHUK_DUCK = 45;

class Hero : public Unit {
  private:
    boolean _isDucking, _isJumping, _isAttacking, _attackSound;
    Rect _attackArea;
    Attack _attack;
    ArduinoNunchuk *_nunchuk;

  public:
    Hero(ArduinoNunchuk* nunchuk);
    boolean getAttackSound(); //Less expensive than directly retrieving the variable.
    void initialize();
    void updateAI(byte dTime, Logic *logic);
};
#endif
