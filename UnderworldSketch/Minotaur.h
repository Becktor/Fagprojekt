#ifndef minotaur_h
#define minotaur_h

#include "Logic.h"
#include "Unit.h"
#include "Sprites.h"
#include "Geo.h"


const static byte
    MINO_HEALTH = 3,
    MINO_ACC_WALK = 1,
    MINO_SPEED_WALK = 3,
    MINO_ACC_CHARGE = 5,
    MINO_SPEED_CHARGE = 8,
    //MINO_HEIGHT = MINOW_HEIGHT,
    MINO_HITBOX_WIDTH = 32,
    //MINO_IMAGE_WIDTH = MINOW_WIDTH,
    //MINO_WALKING_HANDLE = MINOW_HANDLE,
    //MINO_WALKING_CELLS = MINOW_CELLS - 1,
    MINO_WALKING_FR = 75,
    //MINO_CHARGING = MINOC_HANDLE,
    //MINO_CHARGING_CELLS = MINOC_CELLS - 1,
    MINO_CHARGING_FR = 50,
    //MINO_DYING = MINOD_HANDLE,
    //MINO_DYING_CELLS = MINOD_CELLS - 1,
    MINO_DYING_FR = 5,

    MINO_SEE_HERO_DIST = 150,
    MINO_LOSE_HERO_DIST = 100;


class Minotaur : public Unit {
  public:
    boolean _detected, _charge;
    int _distToHeroX, _distToHeroY, _minoMiddle, _distance, _heroXpos, _heroYpos, _heroHeight, _distDiff;

    Minotaur();
    void collideX();
    void initialize();
    void updateAI(int dTime, Logic *logic);
};
#endif

