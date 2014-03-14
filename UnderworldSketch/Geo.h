/*
 *  Utility class describing points and rectangles on a plane.
 */

#ifndef geo_h
#define geo_h

#include "Arduino.h"

class Point
{
  private:
    int _x;
    int _y;
  
  public:
    Point();
    Point(int x, int y);
    int getX();
    int getY();
    void setPoint(int x, int y);
    void setX(int x);
    void setY(int y);
};

class Rect
{
  int _width;
  int _height;
  Point _pos;

  public:
    Rect();
    Rect(Point pos, int width, int height);
    boolean contains(Point p);
    boolean contains(Rect r);
    Point getPos();
    int getWidth();
    int getHeight();
    void setRect(Point pos, int width, int height);
    void setPos(Point pos);
    void setWidth(int width);
    void setHeight(int height);
};

#endif
