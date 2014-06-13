#include "Geo.h"
//some change
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

void Rect::translate(int x, int y) {
  _x += x;
  _y += y;
}
