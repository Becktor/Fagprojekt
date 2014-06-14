#ifndef minotaur_h
#define minotaur_h

#include "Logic.h"
#include "Unit.h"
#include "Sprites.h"
#include "Geo.h"


const static byte
    MINO_ACC_AIR = 1,
    MINO_ACC_BRAKE = 1,
    MINO_ACC_CHARGE = 5,
    MINO_ACC_WALK = 1,
    MINO_ATT_DAMAGE = 1,
    MINO_ATT_FORCE = 8,
    MINO_FR_WALKING = 75,
    MINO_FR_CHARGING = 50,
    MINO_FR_DYING = 255,
    MINO_HEALTH = 3,
    MINO_HITBOX_WALK_WIDTH = 32,
    MINO_HITBOX_WALK_HEIGHT = 43,
    //MINO_HITBOX_CHARGE_WIDTH = 45,
    //MINO_HITBOX_CHARGE_HEIGHT = 25,
    MINO_JUMP = 15,
    MINO_LOS = 200, //Line of sight
    MINO_SCORE = 10,
    MINO_SPEED_AIR = 1,
    MINO_SPEED_HUNT = 2,
    MINO_SPEED_WALK = 1,
    MINO_SPEED_CHARGE = 6,
    //MINO_DETECT_RANGE = 40, //Always detect dist. Doesn't ignore tiles.
    MINO_UNDETECT_RANGE = 250;

class Minotaur : public Unit {
  public:
    boolean _heroDetected, _isCharging;

    Minotaur();
    void collideX();
    boolean detect(Rect *heroHitbox, Logic *logic);
    void hit(byte damage, char force);
    void initialize();
    void updateAI(byte dTime, Logic *logic);
};
#endif

