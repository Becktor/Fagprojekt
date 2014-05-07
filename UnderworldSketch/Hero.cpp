#include "Geo.h"
#include "Logic.h"
#include "Unit.h"
#include "Hero.h"
#include "Prop.h"

Hero::Hero(int x, int y, ArduinoNunchuk* nunchuk ) : 
Unit(Rect(Point(x, y), HERO_WIDTH, HERO_HEIGHT_STAND)) {
  _nunchuk = nunchuk;
  _duck = false;
}

void Hero::updateAI(int dTime, Logic *logic) { //dtime is still unused
  Rect* hitbox = getHitbox();

  //Hero x-movement
  if((130 < _nunchuk->analogX) && (_nunchuk->analogX < 160)){
    setXVel(HERO_SPEED_WALK);
    setDir(RIGHT);  
  }
  else if(_nunchuk->analogX > 160){
    setXVel(HERO_SPEED_RUN);
    setDir(RIGHT); 
  }
  else if((80 < _nunchuk->analogX) && (_nunchuk->analogX < 110)){
    setXVel(-HERO_SPEED_WALK);
    setDir(LEFT);
  }
  else if((15 < _nunchuk->analogX) && (_nunchuk->analogX < 80)){
    setXVel(-HERO_SPEED_RUN);
    setDir(LEFT);
  }
  else 
    setXVel(0);

  //Hero duck - If analogX is lower than 90
  if (45 > _nunchuk -> analogY) {
    if(!_duck) {
      hitbox->setHeight(HERO_HEIGHT_DUCK);
      hitbox-> translate(0, HERO_HEIGHT_STAND - HERO_HEIGHT_DUCK);
      _duck = true;
    }
  } else if(_duck) {
    hitbox->setHeight(HERO_HEIGHT_STAND);
    hitbox->translate(0, HERO_HEIGHT_DUCK - HERO_HEIGHT_STAND);
    _duck = false;
  }
  //Hero jump
  if (_nunchuk->cButton && logic->isGrounded(this)) {
    setYVel(-HERO_SPEED_JUMP);
  }

  //Hero attack
  if (_nunchuk->zButton) {
    if(_duck && logic->atExit(this)) {
      logic->setGameOver(true, true);
    } else {
      //Attack animation trigger
    }
  }
}
