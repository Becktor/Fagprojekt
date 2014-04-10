#include "Direction.h"
#include "Geo.h"
#include "Logic.h"
#include "Unit.h"
#include "Minotaur.h"

void Minotaur::update(int dTime, Logic logic) { //dtime is still unused
 logic.moveUnitHoriz(this, 0);
}
