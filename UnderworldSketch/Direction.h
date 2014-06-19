/*
 *  Direction enumeration. Their values are used in numerous calculations.
 */

#ifndef direction_h
#define direction_h

enum Direction{
  LEFT = -1,
  RIGHT = 1,
  UP = -1,
  DOWN = 1
};

char randDir();
char getDirection(int x);
#endif
