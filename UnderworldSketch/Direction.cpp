#include <Arduino.h>
#include "Direction.h"

char randDir() {
  return random(2) * 2 - 1;
}
