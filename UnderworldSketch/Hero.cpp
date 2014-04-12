#include "Geo.h"
#include "Logic.h"
#include "Unit.h"
#include "Hero.h"
#include <Wire.h>
#include <ArduinoNunchuk.h>

Hero::Hero(int x, int y) : Unit(Rect(Point(x, y), WIDTH, HEIGHT_STAND)) {
  nunchuk = ArduinoNunchuk();
}

void Hero::updateAI(int dTime, Logic *logic) { //dtime is still unused
  //----------------Hero x-movement-----------------------
  if((130 < nunchuk.analogX) && (nunchuk.analogX < 160))
    setXVel(SPEED_WALK);
  else if(nunchuk.analogX > 160)
    setXVel(SPEED_RUN);
  else if((80 < nunchuk.analogX) && (nunchuk.analogX < 110))
    setXVel(-SPEED_WALK);
  else if(80 > nunchuk.analogX)
    setXVel(-SPEED_RUN);
  else
    setXVel(0);


  //-----------------Hero jump---------------------
  if (nunchuk.cButton == 1)
    setYVel(SPEED_JUMP);

  //----------------Hero duck----------------------
  Rect *hitbox = getHitbox();
  if (nunchuk.zButton == 1) {
    hitbox->setHeight(HEIGHT_DUCK);
    hitbox->translate(0, HEIGHT_STAND - HEIGHT_DUCK);
  } else
    hitbox->setHeight(HEIGHT_STAND);
}
