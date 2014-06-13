#ifndef minotaur_h
#define minotaur_h

#include "Logic.h"
#include "Unit.h"
#include "Sprites.h"
#include "Geo.h"


const static byte
    MINO_ACC_STOP = 1,
    MINO_HEALTH = 3,
    MINO_SCORE = 10,
    MINO_ACC_WALK = 1,
    MINO_SPEED_WALK = 3,
    MINO_ACC_CHARGE = 5,
    MINO_SPEED_CHARGE = 8,
    MINO_WALKING_HITBOX_WIDTH = 32,
    MINO_WALKING_HITBOX_HEIGHT = 43,
    MINO_CHARGING_HITBOX_WIDTH = 45,
    MINO_CHARGING_HITBOX_HEIGHT = 25,
    MINO_WALKING_FR = 75,
    MINO_CHARGING_FR = 50,
    MINO_DYING_FR = 255,
    MINO_LOS = 200, //Line of sight
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

