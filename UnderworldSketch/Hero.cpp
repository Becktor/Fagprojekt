#include "Geo.h"
#include "Logic.h"
#include "Unit.h"
#include "Hero.h"
#include <Wire.h>
#include <ArduinoNunchuk.h>


Hero::Hero(int x, int y, ArduinoNunchuk* nunchuk ) : Unit(Rect(Point(x, y), WIDTH, HEIGHT_STAND)) {
 _nunchuk = nunchuk;
}

void Hero::updateAI(int dTime, Logic *logic) { //dtime is still unused
//  _nunchuk->update();
  //----------------Hero x-movement-----------------------
  if((130 < _nunchuk->analogX) && (_nunchuk->analogX < 160))
    setXVel(SPEED_WALK);
  else if(_nunchuk->analogX > 160)
    setXVel(SPEED_RUN);
  else if((80 < _nunchuk->analogX) && (_nunchuk->analogX < 110))
    setXVel(-SPEED_WALK);
  else if((20 < _nunchuk->analogX) && (_nunchuk->analogX < 80))
    setXVel(-SPEED_RUN);
  else 
    setXVel(0);

  //-----------------Hero jump---------------------
  if (_nunchuk->cButton == 1)
    setYVel(SPEED_JUMP);

  //----------------Hero duck----------------------
  Rect *hitbox = getHitbox();
  if (_nunchuk->zButton == 1) {
    hitbox->setHeight(HEIGHT_DUCK);
    hitbox->translate(0, HEIGHT_STAND - HEIGHT_DUCK);
  } else
    hitbox->setHeight(HEIGHT_STAND);
}

