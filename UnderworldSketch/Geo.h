/*
 *  Utility class describing points and rectangles on a plane.
 *  Possibly is redundant, since there is an official point
 *  class (apparently).
 */

#ifndef geo_h
#define geo_h

#include <Arduino.h>

class Point
{
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

class Rect
{
  private:
    int _width;
    int _height;
    Point _pos;

  public:
    //Rect();
    Rect(int x, int y, int width, int height);
    //Rect(Rect *rect);
    boolean contains(Point *p);
    boolean contains(Rect *r);
    Point* getPos();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void translate(int x, int y);
    void setRect(Point pos, int width, int height);
    void setPos(Point pos);
    void setWidth(int width);
    void setHeight(int height);
};
#endif
