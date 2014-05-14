#include "Geo.h"

Point::Point(int x, int y) {
  setPoint(x, y);
}

int Point::getX() {
  return _x;
}

int Point::getY() {
  return _y;
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
  setWidth(width);
  setHeight(height);
}

boolean Rect::contains(Rect *r) {
  return r->getX() < _pos.getX() + _width
      && r->getX() + r->getWidth() > _pos.getX()
      && r->getY() < _pos.getY() + _height
      && r->getY() + r->getHeight() > _pos.getY();
}

int Rect::getX() {
  return _pos.getX();
}

int Rect::getY() {
  return _pos.getY();
}

int Rect::getWidth() {
  return _width;
}

int Rect::getHeight() {
  return _height;
}

void Rect::translate(int x, int y) {
  _pos.translate(x, y);
}

void Rect::setPos(int x, int y) {
  _pos.setPoint(x, y);
}

void Rect::setWidth(byte width) {
  _width = width;
}

void Rect::setHeight(byte height) {
  _height = height;
}
