#include "Logic.h"
#include "Unit.h"
#include "Minotaur.h"

Minotaur::Minotaur() : Unit(MINO_WIDTH, MINO_HEIGHT, MINO_HEALTH, MINO_WIDTH) { }

void Minotaur::fillHealth() {
  setHealth(MINO_HEALTH);
}

void Minotaur::updateAI(int dTime, Logic *logic) { //dtime is still unused
if(getDir() == -1) {
    _xVel = MINO_CSPEED * getDir();
    setHandle(MINO_CHARGING);
    setCells(MINO_CHARGING_CELLS);
  } else {
    _xVel = MINO_WSPEED * getDir();
    setHandle(MINO_WALKING);
    setCells(MINO_WALKING_CELLS);
  }
}

void Minotaur::xCollide() {
  _xVel = 0;
  toggleDir();
}
