#include "Geo.h"
#include "Logic.h"
#include "Unit.h"
#include "Hero.h"
#include <Wire.h>
#include <ArduinoNunchuk.h>

ArduinoNunchuk nunchuk = ArduinoNunchuk();

Hero::Hero(int x, int y) : Unit(Rect(Point(x, y), WIDTH, HEIGHT_STAND)) { }

void Hero::updateAI(int dTime, Logic *logic) { //dtime is still unused
  int xVel;
  int yVel;

  //----------------Hero x-movement-----------------------
  if((130 < nunchuk.analogX) && (nunchuk.analogX < 160))
    xVel = SPEED_WALK;
  else if(nunchuk.analogX > 160)
    xVel = SPEED_RUNNING;
  else if((80 < nunchuk.analogX) && (nunchuk.analogX < 110))
    xVel = SPEED_WALK; 
  else if(80 > nunchuk.analogX)
    xVel = SPEED_RUNNING;
  else
    xVel = 0;

  //-----------------Hero jump---------------------
  if (nunchuk.cButton == 1)
    Hero::setYVel(SPEED_JUMP);

  //----------------Hero duck----------------------
  Rect *hitbox = getHitbox();
  if (nunchuk.zButton == 1) {
    hitbox->setHeight(HEIGHT_DUCK);
    hitbox->translate(0, HEIGHT_STAND - HEIGHT_DUCK);
  } else
    hitbox->setHeight(HEIGHT_STAND);
  setXVel(xVel);
}
