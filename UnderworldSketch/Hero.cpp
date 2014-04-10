#include "Direction.h"
#include "Geo.h"
#include "Logic.h"
#include "Unit.h"
#include "Hero.h"
#include <Wire.h>
#include <ArduinoNunchuk.h>
ArduinoNunchuk nunchuk = ArduinoNunchuk();

#define HERO_STAND_HEIGHT 20 //Height stand value
#define HERO_DUCK_HEIGHT 10 //Duck height
#define HERO_WIDTH 10
#define HERO_JUMP 2
#define HERO_WALK 1
#define HERO_RUNNING 3

void Hero::update(int dTime, Logic logic) { //dtime is still unused
  //----------------Hero x-movement-----------------------
  int dX;
  if ((130  <  nunchuk.analogX)  && (nunchuk.analogX < 160)) {
    dX = HERO_WALK;
  }
  else if(nunchuk.analogX > 160 ) {
    dX = HERO_RUNNING;
  }
  else if ((80 < nunchuk.analogX )  && ( nunchuk.analogX < 110 )) {
    dX = HERO_WALK; 
  }
  else if (80 > nunchuk.analogX) {
    dX = HERO_RUNNING;
  } else {
    dX = 0;
  }

  //-----------------Hero jump---------------------
  if (nunchuk.cButton == 1 && !isFalling()) {
    Hero::setYVel(HERO_JUMP);
    setFalling(true);
  }

  //----------------Hero duck----------------------
  Rect *hitbox = getHitbox();
  if (nunchuk.zButton == 1) {
    hitbox->setHeight(HERO_DUCK_HEIGHT);
    hitbox->translate(0, HERO_STAND_HEIGHT - HERO_DUCK_HEIGHT);
  } else {
    hitbox->setHeight(HERO_STAND_HEIGHT);
  }

  //Excecution
  logic.moveUnitHoriz(this, dX);
  //if(!logic.moveUnitVerti(this, getYVel())) {
  //  setYVel(0);
  //  setFalling(false);
  //}
}
