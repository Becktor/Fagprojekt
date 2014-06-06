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

Rect::Rect(int x, int y, byte width, byte height) : _pos(x, y) {
  _width = width;
  _height = height;
}

boolean Rect::contains(Rect *r) {
  return r->getX() < getX() + _width
      && r->getX() + r->_width > getX()
      && r->getY() < getY() + _height
      && r->getY() + r->_height > getY();
}

int Rect::getX() {
  return _pos._x;
}

int Rect::getY() {
  return _pos._y;
}

void Rect::translate(int x, int y) {
  _pos.translate(x, y);
}

void Rect::setPos(int x, int y) {
  _pos.setPoint(x, y);
}
