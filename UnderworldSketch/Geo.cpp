#include "Direction.h"
#include "Geo.h"

Point::Point() {
  setPoint(0, 0);
}

void Point::setPoint(int x, int y) {
  _x = x;
  _y = y;
}

Rect::Rect(byte width, byte height) {
  _x = 0;
  _y = 0;
  _width = width;
  _height = height;
}

boolean Rect::contains(Rect *r) {
  return r->_x < _x + _width
      && r->_x + r->_width > _x
      && r->_y < _y + _height
      && r->_y + r->_height > _y;
}

void Rect::setPos(int x, int y) {
  _x = x;
  _y = y;
}

int Rect::side(char dir) {
  if(dir == LEFT)
    return _x;
  else
    return _x + _width - 1;
}

int Rect::surface(char dir) {
  if(dir == UP)
    return _y;
  else
    return _y + _height - 1;
}

void Rect::translate(int x, int y) {
  _x += x;
  _y += y;
}
