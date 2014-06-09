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
    accelerate(MINO_ACC_WALK, dir * MINO_SPEED_WALK);
    setHandle(MINO_WALKING);
    setCells(MINO_WALKING_CELLS);
  } //else Falling?
}

void Minotaur::xCollide() {
  _xVel = 0;
  toggleDir();
}
