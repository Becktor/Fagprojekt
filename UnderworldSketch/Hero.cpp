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
#define HERO_JUMP_ACC 2
#define HERO_WALK 1
#define HERO_RUNNING 3;

void Hero::update(int dTime, Logic logic) { //dtime is still unused
  int dX;
  int dY;

  //----------------Hero x-movement-----------------------
  if ( (130  <  nunchuk.analogX)  && (nunchuk.analogX < 160) ){
    dX =  HERO_WALK;
  }
  else if(  nunchuk.analogX > 160 ){
    dX =  HERO_RUNNING;
  }
  else if ((80 < nunchuk.analogX )  && ( nunchuk.analogX < 110 ) ){
    dX =  HERO_WALK; 
  }
  else if (  80 > nunchuk.analogX){
    dX =  HERO_RUNNING;
  }

  //-----------------Hero jump---------------------
  if ( nunchuk.cButton == 1 ) {
    Hero::setYAcc(2);
  } else {
    Hero::setYAcc(1);
  }

  //----------------Hero duck----------------------
  if (nunchuk.zButton == 1) {
    _hitbox.setHeight(HERO_DUCK_HEIGHT);
  }
  else {
    _hitbox.setHeight(HERO_STAND_HEIGHT);
  }
  logic.moveUnitHoriz(this, dX);
}
