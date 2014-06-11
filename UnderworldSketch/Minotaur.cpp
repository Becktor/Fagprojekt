#include "Direction.h"
#include "Logic.h"
#include "Unit.h"
#include "Minotaur.h"

Minotaur::Minotaur() : Unit(MINO_WIDTH, MINO_HEIGHT, MINO_HEALTH, MINO_IMAGE_WIDTH) { }

void Minotaur::initialize() {
  Unit::initialize();
  _health = MINO_HEALTH;
}

void Minotaur::updateAI(int dTime, Logic *logic) { //dtime is still unused
  if(logic->isGrounded(this)) {
    if(!logic->isWalkable(_hitbox._x + (1 + _dir) * _hitbox._width / 2, _hitbox._y + _hitbox._height))
      toggleDir();
    if(_handle != MINO_WALKING) {
      setCurrentCell(0);
      _handle = MINO_WALKING;
      _cells = MINO_WALKING_CELLS;
      setFR(MINO_WALKING_FR);
    }
    accelerate(MINO_ACC_WALK, _dir * MINO_SPEED_WALK);

    //detection
    Prop* hero = logic->getHero();
    heroXpos = hero->_hitbox._x;
    heroYpos = hero->_hitbox._y;
    if (_hitbox._x < heroXpos){   //Substract largest from the smaller value - 'Distances'
      distToHeroX = heroXpos-_hitbox._x;
    }
    else{
      distToHeroX =  _hitbox._x - heroXpos;
    }
    if (_hitbox._y < hero->_hitbox._y){
      distToHeroY =  heroYpos - _hitbox._y;
    }
    else{
      distToHeroY = _hitbox._y - heroYpos;
    }
    distance = sqrt(distToHeroX * distToHeroX + distToHeroY*distToHeroY);
    if( (heroYpos==_hitbox._y) && distToHeroX < 100) {
      if((_dir == RIGHT && heroXpos > _hitbox._x) || (_dir == LEFT && heroXpos < _hitbox._x)){
      }
    }
    if (distance > 200 && detected == true){  //Hero ran away!
    }

  } //else Falling?
}

void Minotaur::xCollide() {
  _xVel = 0;
  toggleDir();
}
