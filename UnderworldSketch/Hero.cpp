#include "Geo.h"
#include "Logic.h"
#include "Unit.h"
#include "Hero.h"



Hero::Hero(int x, int y, ArduinoNunchuk* nunchuk ) : Unit(Rect(Point(x, y), WIDTH, HEIGHT_STAND)) {
 _nunchuk = nunchuk;
}

void Hero::updateAI(int dTime, Logic *logic) { //dtime is still unused
  boolean duck;
  boolean jump;
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
  if (_nunchuk-> cButton == 1 & !jump) {
    setYVel(SPEED_JUMP);
    jump = true; 
  }

  //----------------Hero duck----------------------//If lower than 90
  Rect *hitbox = getHitbox();
  if (  90 > _nunchuk -> analogY  ) {
    hitbox->setHeight(HEIGHT_DUCK);
    hitbox->translate(0, HEIGHT_STAND - HEIGHT_DUCK);
  } else
    hitbox->setHeight(HEIGHT_STAND);
    jump = false;
}  

