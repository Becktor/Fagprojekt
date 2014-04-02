#include "Direction.h"
#include "Geo.h"
#include "Logic.h"
#include "Unit.h"
#include "Hero.h"




void Hero::update(int dTime, Logic logic) { //dtime is still unused
 
  logic.moveUnitHoriz(this, getSpeed() );
}



