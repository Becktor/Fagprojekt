#include "Direction.h"
#include "Logic.h"
#include "Unit.h"
#include "Minotaur.h"

Minotaur::Minotaur() : Unit(MINO_WIDTH, MINO_HEIGHT, MINO_HEALTH, MINO_IMAGE_WIDTH) { }

void Minotaur::fillHealth() {
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
    accelerate(MINO_ACC_WALK, _dir * MINO_SPEED_WALK);

    //detection
    Prop* hero = logic->getHero();
    heroXpos = hero->_hitbox._x;
    heroYpos = hero->_hitbox._y;
    distToHeroX = abs(heroXpos - _hitbox._x);
    distToHeroY = abs(heroYpos - _hitbox._y);
    distance = sqrt((distToHeroX * distToHeroX) + (distToHeroY * distToHeroY));

    //if(((_hitbox._y - _hitbox._height) <= heroXpos <= (_hitbox._y +_hitbox._height))) {
    //Serial.print(heroYpos);
    //Serial.print("----");
    //Serial.println(_hitbox._y);
    if (!_detected){
     if(((_hitbox._y - _hitbox._height) <= heroXpos <= (_hitbox._y +_hitbox._height))) {
       if((distToHeroX <= MINO_SEE_HERO_DIST) && ((_dir == RIGHT && heroXpos > _hitbox._x) || (_dir== LEFT &&  heroXpos < _hitbox._x))){
           Serial.println("See ya");
           _detected = true;
           _unfollow = false;
        }
       }
    }
    if (_detected || _unfollow && (distance > MINO_LOSE_HERO_DIST)){  //Hero ran away!
      Serial.println("where are you?!");
      _detected = false;
      _unfollow = true;
    }

  } //else Falling?
}

void Minotaur::xCollide() {
  _xVel = 0;
  toggleDir();
}

