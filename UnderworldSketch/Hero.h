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
    //Acceleration values
    HERO_ACC_AIR = 1,
    HERO_ACC_DUCK = 1,
    HERO_ACC_RUN = 2,
    HERO_ACC_WALK = 1,
    //Attack variables
    HERO_ATT_DAMAGE = 1,
    HERO_ATT_FORCE = 5,
    HERO_ATT_RANGE = 48,
    //Initial Hitpoints
    HERO_HEALTH = 5,
    //Hitbox Dimensions
    HERO_HITBOX_HEIGHT_STAND = 38, 
    HERO_HITBOX_HEIGHT_DUCK = 18, 
    HERO_HITBOX_WIDTH = 24,
    //Vertical Jump Velocity
    HERO_JUMP = 15,
    //Target Speed Values (Maximum speed in each state)
    HERO_SPEED_AIR = 2,
    HERO_SPEED_DUCK = 2,
    HERO_SPEED_RUN = 6,
    HERO_SPEED_WALK = 3,
    //Thumbstick Thresholds
    NUNCHUK_REST_X = 120, //When the thumbstick is at rest.
    NUNCHUK_WALK = 10,
    NUNCHUK_RUN = 50,
    NUNCHUK_DUCK = 45;

const static word 
    //Time Intervals between Bitmap Cells
    HERO_FR_ATTACKING = 80,
    HERO_FR_DUCKING = 100,
    HERO_FR_IDLE = 200,
    HERO_FR_FALL = 1000,
    HERO_FR_JUMP = 1000,
    HERO_FR_RUNNING = 100,
    HERO_FR_WALKING = 200,
    //time interval in which the hero is invulnerable
    HERO_INV_TIME = 1000;

class Hero : public Unit {
  private:
    boolean _isDucking, _isJumping, _isAttacking, _attackSound;
    Rect _attackArea;
    Attack _attack;
    ArduinoNunchuk *_nunchuk;

  public:
    Hero(ArduinoNunchuk* nunchuk);
    boolean getAttackSound(); //Less expensive than directly retrieving the variable.
    void hit(byte damage, char force);
    void initialize();
    void updateAI(byte dTime, Logic *logic);
};
#endif
