/*
 *  Utility class describing points and rectangles on a plane.
 *  Possibly is redundant, since there is an official point
 *  class (apparently).
 */

#ifndef geo_h
#define geo_h

#include <Arduino.h>

class Point {
  private:
    int _x;
    int _y;
  
  public:
    Point(int x, int y);
    int getX();
    int getY();
    void translate(int x, int y);
    void setPoint(int x, int y);
};

class Rect {
  private:
    byte _width;
    byte _height;
    Point _pos;

  public:
    Rect(int x, int y, byte width, byte height);
    boolean contains(Rect *r);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void translate(int x, int y);
    void setPos(int x, int y);
    void setWidth(byte width);
    void setHeight(byte height);
};

#endif

