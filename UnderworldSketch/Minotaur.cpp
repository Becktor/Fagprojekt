#include "Direction.h"
#include "Sprites.h"
#include "Logic.h"
#include "Unit.h"
#include "Minotaur.h"

Minotaur::Minotaur() : Unit(MINO_WALKING_HITBOX_WIDTH, MINO_WALKING_HITBOX_HEIGHT, MINO_HEALTH, MINO_SCORE, MINO_WALKING_WIDTH) { }

void Minotaur::collideX() {
  _xVel = 0;
  if(_isActive) {
    _isCharging = false;
    toggleDir();
  }
}

boolean Minotaur::detect(Rect *heroHitbox, Logic *logic) {
  int lineOfSight = _hitbox._y + _hitbox._height / 2,
      minoX = _hitbox._x,
      heroX = heroHitbox->_x;
  if(_dir == LEFT) {
    minoX += _hitbox._width - 1;
    heroX += heroHitbox->_width - 1;
  }
  int dist = _dir * (heroX - minoX);
  if((dist <= MINO_LOS + _hitbox._width - 1 &&
      dist > -heroHitbox->_width &&
      heroHitbox->_y <= lineOfSight &&
      heroHitbox->_y + heroHitbox->_height > lineOfSight) ||
      _hitbox.contains(heroHitbox)) {
    char tileY = worldToGrid(lineOfSight),
         tileXStart = worldToGrid(minoX),
         tileXEnd = worldToGrid(heroX);
    for(char tileX = tileXStart; _dir * tileX <= _dir * tileXEnd; tileX += _dir)
      if(logic->tileIsSolid(tileX, tileY))
        return false;
    _isCharging = true;
    _heroDetected = true;
    return true;
  } else
    return false;
}

void Minotaur::hit(byte damage, char force) {
  Unit::hit(damage, force);
  _heroDetected = true;
}

void Minotaur::initialize() {
  Prop::initialize();
  newHandle(MINO_WALKING_HANDLE, MINO_WALKING_CELLS, MINO_WALKING_FR);
  _health = MINO_HEALTH;
  _heroDetected = false;
  _isCharging = false;
}

void Minotaur::updateAI(byte dTime, Logic *logic) { //dtime is still unused
  byte acc;
  char targetSpeed = 0;
  if(logic->isGrounded(this)) {
    if(_isActive) {
      Rect *heroHitbox = &(logic->_hero->_hitbox);
      if(_isCharging || detect(heroHitbox, logic)) { //Charge
        acc = MINO_ACC_CHARGE;
        targetSpeed = _dir * MINO_SPEED_CHARGE;
        newHandle(MINO_CHARGING_HANDLE, MINO_CHARGING_CELLS, MINO_CHARGING_FR);
      } else {
        acc = MINO_ACC_WALK;
        newHandle(MINO_WALKING_HANDLE, MINO_WALKING_CELLS, MINO_WALKING_FR);
        if(!logic->isWalkable(_hitbox._x + (1 + _dir) * _hitbox._width / 2, _hitbox._y + _hitbox._height))
          toggleDir();
        targetSpeed = _dir * MINO_SPEED_WALK;
        /*
        if(_heroDetected && _hitbox(heroHitbox) < MINO_DETECT_DIST) < MINO_DETECT_DIST) { //Hunt
          
        } else { //Wander
          _heroDetected = false;
          if(!logic->isWalkable(_hitbox._x + (1 + _dir) * _hitbox._width / 2, _hitbox._y + _hitbox._height))
            toggleDir();
          targetSpeed = dir * MINO_SPEED_WALK;
        }
        */
      }
    } else { //Dying
      newHandle(MINO_DYING_HANDLE, MINO_DYING_CELLS, MINO_DYING_FR);
      acc = MINO_ACC_BRAKE;
    }
  } else //Flying
    acc = 0;
  _xVel = zoomIn(acc, _xVel, targetSpeed);
}
