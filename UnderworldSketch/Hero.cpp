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
  //  _nunchuk->update();
  //----------------Hero x-movement-----------------------
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

  //-----------------Hero jump---------------------//if higher than 140
  Serial.begin(19200);
  
    if (_nunchuk->cButton && logic->isSolid(hitbox->getX(),hitbox->getY()+(hitbox->getHeight()+1))) {
      setYVel(-SPEED_JUMP);
      Serial.println("carstendinlort");
     
  }

  //----------------Hero duck----------------------//If lower than 90
  if (  90 > _nunchuk -> analogY  ) {
    hitbox->setHeight(HEIGHT_DUCK);
    if(!duck)
      hitbox->translate(0, HEIGHT_STAND - HEIGHT_DUCK);
    duck = true;
  } else{
      hitbox->setHeight(HEIGHT_STAND);
      duck=false;
  }
}  

