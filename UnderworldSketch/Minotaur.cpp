#include "Logic.h"
#include "Unit.h"
#include "Minotaur.h"

Minotaur::Minotaur() : Unit(MINO_WIDTH, MINO_HEIGHT, MINO_HEALTH, MINO_IMAGE_WIDTH) { }

void Minotaur::fillHealth() {
  setHealth(MINO_HEALTH);
}

void Minotaur::updateAI(int dTime, Logic *logic) { //dtime is still unused
  char dir = getDir();
  if(logic->isGrounded(this)) {
    
    
    if(!logic->isWalkable(_hitbox._x + (1 + dir) * _hitbox._width / 2, _hitbox._y + _hitbox._height))
      toggleDir();
      
    if(getHandle() != MINO_WALKING)
    {
      setCurrentCell(0);
      setHandle(MINO_WALKING);
      setCells(MINO_WALKING_CELLS);
      setFR(MINO_WALKING_FR);
    }
    accelerate(MINO_ACC_WALK, dir * MINO_SPEED_WALK);
  } //else Falling?
}

void Minotaur::xCollide() {
  _xVel = 0;
  toggleDir();
}
