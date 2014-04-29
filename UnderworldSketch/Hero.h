#ifndef hero_h
#define hero_h

#include "Direction.h"
#include "Logic.h"
#include <Wire.h>
#include <ArduinoNunchuk.h>

#define HEIGHT_STAND 40 //Height stand value
#define HEIGHT_DUCK 20 //Duck height
#define WIDTH 30
#define SPEED_JUMP 15
#define SPEED_WALK 1
#define SPEED_RUN 5

class Hero : public Unit {
  private:
    ArduinoNunchuk *_nunchuk;
    boolean duck;

  public:
    Hero(int x, int y, ArduinoNunchuk* nunchuk);
    void updateAI(int dTime, Logic *logic);
};
#endif
