#include "Direction.h"
#include "Logic.h"
#include "Minotaur.h"

Minotaur::Minotaur(int x, int y) : Unit(Rect(Point(x, y), WIDTH, HEIGHT)) { }

Direction Minotaur::getDir() {
  return _dir;
}

void Minotaur::toggleDir() {
  if(_dir = Left)
    _dir = Right;
  else
    _dir = Left;
}

void Minotaur::updateAI(int dTime, Logic *logic) { //dtime is still unused
  
}
