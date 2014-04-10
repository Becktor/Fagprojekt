#ifndef minotaur_h
#define minotaur_h

#include "Direction.h"
#include "Geo.h"
#include "Logic.h"

class Logic;
class Minotaur : Unit {
  public:
    void update(int dTime, Logic logic);
};
#endif
