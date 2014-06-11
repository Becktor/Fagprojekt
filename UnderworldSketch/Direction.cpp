#include <Arduino.h>
#include "Direction.h"

char randDir() {
  if(random(2) == 0)
    return LEFT;
  else
    return RIGHT;
}

char getDirection(char x) {
  if(x == 0)
    return 0;
  else if(x > 0)
    return RIGHT;
  else
    return LEFT;
}
