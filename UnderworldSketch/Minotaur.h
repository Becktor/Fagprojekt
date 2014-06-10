#ifndef minotaur_h
#define minotaur_h

#include "Logic.h"
#include "Unit.h"
#include "Sprites.h"

const static byte
    
    MINO_HEALTH = 3,
    MINO_ACC_WALK = 1,
    MINO_SPEED_WALK = 5,
    MINO_ACC_CHARGE = 3,
    MINO_SPEED_CHARGE = 8,
    MINO_HEIGHT = MINOW_HEIGHT,
    MINO_WIDTH = 32,
    MINO_IMAGE_WIDTH = MINOW_WIDTH,
    MINO_WALKING = MINOW_HANDLE,
    MINO_WALKING_CELLS = MINOW_CELLS - 1,
    MINO_WALKING_FR = 75,
    MINO_CHARGING = MINOC_HANDLE,
    MINO_CHARGING_CELLS = MINOC_CELLS - 1,
    MINO_CHARGING_FR = 5,
    MINO_DYING = MINOD_HANDLE,
    MINO_DYING_CELLS = MINOD_CELLS - 1,
    MINO_DYING_FR = 5;


class Minotaur : public Unit {
  public:
    Minotaur();
    void fillHealth();
    void updateAI(int dTime, Logic *logic);
    void xCollide();
};
#endif
