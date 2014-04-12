#ifndef hero_h
#define hero_h

#include "Direction.h"
#include "Logic.h"
#include <Wire.h>
#include <ArduinoNunchuk.h>

#define HEIGHT_STAND 20 //Height stand value
#define HEIGHT_DUCK 10 //Duck height
#define WIDTH 10
#define SPEED_JUMP 2
#define SPEED_WALK 1
#define SPEED_RUN 3

class Hero : public Unit {
  private:
    ArduinoNunchuk nunchuk;

  public:
    Hero(int x, int y);
    void updateAI(int dTime, Logic *logic);
};
#endif
