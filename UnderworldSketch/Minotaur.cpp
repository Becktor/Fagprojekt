#include "Direction.h"
#include "Logic.h"
#include "Minotaur.h"

Minotaur::Minotaur(int x, int y) : Unit(Rect(Point(x, y), WIDTH, HEIGHT)) {
  if(random(2) == 0)
    setDir(Left);
  else
    setDir(Right);
}

void Minotaur::updateAI(int dTime, Logic *logic) { //dtime is still unused
  if(getXVel() == 0)
    toggleDir();
  setXVel(SPEED * getDir());
}
