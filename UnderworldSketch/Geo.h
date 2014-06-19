/*
 *  Utility class describing points and rectangles on a plane.
 */

#ifndef geo_h
#define geo_h

#include <Arduino.h>

class Point {
  public:
    int _x;
    int _y;

    Point();
    void setPoint(int x, int y);
};

class Rect {
  public:
    int _x;
    int _y;
    byte _width;
    byte _height;

    Rect(byte width, byte height);
    boolean contains(Rect *r);
    void setPos(int x, int y);
    int side(char dir);
    int surface(char dir);
    void translate(int x, int y);
};
#endif
