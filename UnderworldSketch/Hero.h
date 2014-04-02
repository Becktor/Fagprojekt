/*
 *  Currently non-abstract class of any one unit. Cannot be superclass
 *  to 'Entities' since entities uses points for positions while units use
 *  hitboxes. Could be superclass to future prop though.
 */

#ifndef hero_h
#define hero_h

#include "Direction.h"
#include "Geo.h"
#include "Logic.h"

class Logic;
class Hero : Unit
{

  public:
    void update(int dTime, Logic logic);
};
#endif

