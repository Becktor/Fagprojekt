#include <Arduino.h>
#include "Direction.h"

char randDir() {
  if(random(2) == 0)
    return 1;
  else
    return -1;
}

//Returns the "direction" of the given distance.
//In case of x = 0 it returns LEFT to avoid
//non-direction return issues.
char getDirection(int x) {
  if(x > 0)
    return 1;
  else
    return -1;
}
