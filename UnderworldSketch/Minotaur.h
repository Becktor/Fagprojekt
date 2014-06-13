#ifndef minotaur_h
#define minotaur_h

#include "Logic.h"
#include "Unit.h"
#include "Sprites.h"
#include "Geo.h"


const static byte
    MINO_HEALTH = 3,
    MINO_SCORE = 10,
    MINO_ACC_WALK = 1,
    MINO_SPEED_WALK = 3,
    MINO_ACC_CHARGE = 5,
    MINO_SPEED_CHARGE = 8,
    MINO_SPEED_DYING = 0,
    MINO_WALKING_HITBOX_WIDTH = 32,
    MINO_WALKING_HITBOX_HEIGHT = 43,
    MINO_CHARGING_HITBOX_WIDTH = 45,
    MINO_CHARGING_HITBOX_HEIGHT = 25,
    MINO_WALKING_FR = 75,
    MINO_CHARGING_FR = 50,
    MINO_DYING_FR = 1000,
    MINO_SEE_HERO_DIST = 150,
    MINO_LOSE_HERO_DIST = 100;


class Minotaur : public Unit {
  public:
    boolean _detected, _charge;
    int _distToHeroX, _distToHeroY, _minoMiddle, _distance, _heroXpos, _heroYpos, _heroHeight, _distDiff;

    Minotaur();
    void collideX();
    void initialize();
    void updateAI(byte dTime, Logic *logic);
};
#endif

