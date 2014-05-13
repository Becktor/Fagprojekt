#include "Direction.h"
#include "Logic.h"
#include "Minotaur.h"

Minotaur::Minotaur(int x, int y) : Unit(Rect(x, y, MINO_WIDTH, MINO_HEIGHT), MINO_HEALTH) {
  if(random(2) == 0)
    setDir(LEFT);
  else
    setDir(RIGHT);
}

void Minotaur::updateAI(int dTime, Logic *logic) { //dtime is still unused
  if(getXVel() == 0)
    toggleDir();
  setXVel(MINO_SPEED * getDir());
}
