#include "Logic.h"
#include "Unit.h"
#include "Minotaur.h"

Minotaur::Minotaur() : Unit(MINO_WIDTH, MINO_HEIGHT, MINO_HEALTH) { }

void Minotaur::fillHealth() {
  setHealth(MINO_HEALTH);
}

void Minotaur::updateAI(int dTime, Logic *logic) { //dtime is still unused
  if(getXVel() == 0)
    toggleDir();
    
  if(getDir()==-1)
   {
    setXVel(MINO_RSPEED * getDir());
    setHandle(MINO_RUNNING);
    setCells(MINO_RUNNING_CELLS);
   }
   else
   {
    setXVel(MINO_WSPEED * getDir());
    setHandle(MINO_WALKING);
    setCells(MINO_WALKING_CELLS);
   }
 }

