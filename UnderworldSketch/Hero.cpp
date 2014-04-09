#include "Direction.h"
#include "Geo.h"
#include "Logic.h"
#include "Unit.h"
#include "Hero.h"
#include <Wire.h>
#include <ArduinoNunchuk.h>
ArduinoNunchuk nunchuk = ArduinoNunchuk();

void Hero::update(int dTime, Logic logic) { //dtime is still unused
  int dX;
  
    //Hero movement 
  if ( (130  <  nunchuk.analogX)  && (nunchuk.analogX < 160) ){
   dX =  1;
  }
  else if(  nunchuk.analogX > 160 ){
   dX =  3;
  }
  else if ((80 < nunchuk.analogX )  && ( nunchuk.analogX < 110 ) ){
   dX =  1; ;
  }
  else if (  80 > nunchuk.analogX){
   dX =  3;
  }

  
  
  
  
  logic.moveUnitHoriz(this, dX);
}



