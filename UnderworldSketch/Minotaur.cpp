#include "Logic.h"
#include "Unit.h"
#include "Minotaur.h"

Minotaur::Minotaur() : Unit(MINO_WIDTH, MINO_HEIGHT, MINO_HEALTH) { }

void Minotaur::fillHealth() {
  setHealth(MINO_HEALTH);
}

void Minotaur::updateAI(int dTime, Logic *logic) { //dtime is still unused
  accelerate(MINO_ACC_WALK, getDir() * MINO_SPEED_WALK);
  setHandle(MINO_WALKING);
  setCells(MINO_WALKING_CELLS);
}

void Minotaur::xCollide() {
  _xVel = 0;
  toggleDir();
}
