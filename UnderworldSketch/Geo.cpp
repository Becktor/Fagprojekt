#include "Geo.h"

Point::Point(int x, int y) {
  setPoint(x, y);
}

void Point::translate(int x, int y) {
  _x += x;
  _y += y;
}

void Point::setPoint(int x, int y) {
  _x = x;
  _y = y;
}

Rect::Rect(int x, int y, byte width, byte height) {
  _x = x;
  _y = y;
  _width = width;
  _height = height;
}

boolean Rect::contains(Rect *r) {
  return r->_x < _x + _width
      && r->_x + r->_width > _x
      && r->_y < _y + _height
      && r->_y + r->_height > _y;
}

void Rect::translate(int x, int y) {
  _x += x;
  _y += y;
}

void Rect::setPos(int x, int y) {
  _x = x;
  _y = y;
}
