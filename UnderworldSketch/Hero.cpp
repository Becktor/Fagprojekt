#include "Geo.h"
#include "Logic.h"
#include "Unit.h"
#include "Hero.h"

Hero::Hero(int x, int y, ArduinoNunchuk* nunchuk ) : Unit(Rect(Point(x, y), WIDTH, HEIGHT_STAND)) {
 _nunchuk = nunchuk;
 duck=false;
}

void Hero::updateAI(int dTime, Logic *logic) { //dtime is still unused
  Rect* hitbox = getHitbox();

  //Hero x-movement
  if((130 < _nunchuk->analogX) && (_nunchuk->analogX < 160))
    setXVel(SPEED_WALK);
  else if(_nunchuk->analogX > 160)
    setXVel(SPEED_RUN);
  else if((80 < _nunchuk->analogX) && (_nunchuk->analogX < 110))
    setXVel(-SPEED_WALK);
  else if((15 < _nunchuk->analogX) && (_nunchuk->analogX < 80))
    setXVel(-SPEED_RUN);
  else 
    setXVel(0);

  //Hero duck - If analogX is lower than 90
  if (  90 > _nunchuk -> analogY  ) {
    hitbox->setHeight(HEIGHT_DUCK);
    if(!duck)
      hitbox->translate(0, HEIGHT_STAND - HEIGHT_DUCK);
    duck = true;
  } else{
      hitbox->setHeight(HEIGHT_STAND);
      duck=false;
  }
  //Hero jump
  if (_nunchuk->cButton && logic->isSolid(hitbox->getX(),hitbox->getY()+(hitbox->getHeight()+1))) {
      setYVel(-SPEED_JUMP);
  }

  //Hero attack
  if (_nunchuk->zButton){
    //Attack animation trigger
  }
}  

