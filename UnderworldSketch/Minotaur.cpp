#include "Logic.h"
#include "Minotaur.h"

Minotaur::Minotaur(int x, int y) : Unit(x, y, MINO_WIDTH, MINO_HEIGHT, MINO_HEALTH) { }

void Minotaur::updateAI(int dTime, Logic *logic) { //dtime is still unused
  if(getXVel() == 0)
    toggleDir();
  setXVel(MINO_SPEED * getDir());
}

