#include "Geo.h"

Point::Point() {
  setPoint(0, 0);
}

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
  setX(x);
  setY(y);
}

void Point::setX(int x) {
  _x = x;
}

void Point::setY(int y) {
  _y = y;
}

Rect::Rect() {
  setRect(Point(), 0, 0);
}

Rect::Rect(int x, int y, int width, int height) {
  setRect(Point(x, y), width, height);
}

Rect::Rect(Point pos, int width, int height) {
  setRect(pos, width, height);
}

boolean Rect::contains(Point p) {
  return p.getX() > _pos.getX()
      && p.getX() < _pos.getX() + _width
      && p.getY() > _pos.getY()
      && p.getY() < _pos.getY() + _height;
}

boolean Rect::contains(Rect r) {
  Point p = r.getPos();
  return p.getX() < _pos.getX() + _width
      && p.getX() + r.getWidth() > _pos.getX()
      && p.getY() < _pos.getY() + _height
      && p.getY() + r.getHeight() > _pos.getY();
}

Point Rect::getPos() {
  return _pos;
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

void Rect::setRect(Point pos, int width, int height) {
  setPos(pos);
  setWidth(width);
  setHeight(height);
}

void Rect::setPos(Point pos) {
  _pos = pos;
}

void Rect::setWidth(int width) {
  _width = max(1, width);
}

void Rect::setHeight(int height) {
  _height = max(1, height);
}
