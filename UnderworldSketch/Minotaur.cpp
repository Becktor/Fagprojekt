#include "Direction.h"
#include "Logic.h"
#include "Unit.h"
#include "Minotaur.h"
#include "Sprites.h"

Minotaur::Minotaur() : Unit(MINO_HITBOX_WIDTH, MINO_WALKING_HEIGHT, MINO_HEALTH, MINO_WALKING_WIDTH) { }
  _detected  = false;
}

void Minotaur::initialize() {
  Prop::initialize();
  _health = MINO_HEALTH;
}

void Minotaur::updateAI(int dTime, Logic *logic) { //dtime is still unused
  if(logic->isGrounded(this)) {
    if(!logic->isWalkable(_hitbox._x + (1 + _dir) * _hitbox._width / 2, _hitbox._y + _hitbox._height))
      toggleDir();
    if(_handle != MINO_WALKING_HANDLE) {
      updateHandle(MINO_WALKING_HANDLE, MINO_WALKING_CELLS);
      _FR = MINO_WALKING_FR;
    }

    //detection
    Prop* hero = logic->getHero();
    _heroXpos = hero->_hitbox._x;
    _heroYpos = hero->_hitbox._y;
    _heroHeight = hero->_hitbox._height;
    _distDiff = _heroXpos - _hitbox._x;
    _distToHeroX = abs(_distDiff);
    _distToHeroY = abs(_heroYpos - _hitbox._y);
    _distance = sqrt((_distToHeroX * _distToHeroX) + (_distToHeroY * _distToHeroY));

    if (_distance > MINO_LOSE_HERO_DIST){  //Hero ran away!
      _detected = false;
    }
    if( _heroYpos + _heroHeight <  (((_hitbox._y+_hitbox._height)/2) + _hitbox._y) &&  (((_hitbox._y+_hitbox._height)/2) + _hitbox._y) < _heroYpos) {
      if((_distToHeroX <= MINO_SEE_HERO_DIST)){
        if(((_dir == RIGHT && _heroXpos > _hitbox._x) || (_dir== LEFT &&  _heroXpos < _hitbox._x))){
         _detected = true;
        }
      }
    }
    if (_detected){
    Serial.println("Detected");
    accelerate(MINO_ACC_CHARGE, _dir * MINO_SPEED_CHARGE);
    }
    else{
    Serial.println("Un_Detected");
    accelerate(MINO_ACC_WALK, _dir * MINO_SPEED_WALK);
    }
  } //else Falling?
}

void Minotaur::xCollide() {
  _xVel = 0;
  toggleDir();
}
