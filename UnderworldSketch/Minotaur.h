#ifndef minotaur_h
#define minotaur_h

#include "Direction.h"
#include "Logic.h"

#define SPEED 1
#define HEIGHT 40
#define WIDTH 30

class Minotaur : public Unit {
  private:
    Direction _dir;

  public:
    Minotaur(int x, int y);
    Direction getDir();
    void toggleDir();
    void updateAI(int dTime, Logic *logic);
};
#endif
