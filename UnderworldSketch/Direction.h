#ifndef direction_h
#define direction_h
//Some change
enum Direction{
  LEFT = -1,
  RIGHT = 1,
  UP = -1,
  DOWN = 1
};

char randDir();
char getDirection(char x);
#endif
