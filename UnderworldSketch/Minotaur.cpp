#include "Direction.h"
#include "Logic.h"
#include "Minotaur.h"

Minotaur::Minotaur(int x, int y) : Unit(Rect(Point(x, y), WIDTH, HEIGHT)) {
  if(random(2) == 0)
    _dir = Left;
  else
    _dir = Right;
}

Direction Minotaur::getDir() {
  return _dir;
}

void Minotaur::toggleDir() {
  if(_dir == Left)
    _dir = Right;
  else
    _dir = Left;
}

void Minotaur::updateAI(int dTime, Logic *logic) { //dtime is still unused
  if(getXVel() == 0)
    toggleDir();
  setXVel(SPEED * _dir);
}
