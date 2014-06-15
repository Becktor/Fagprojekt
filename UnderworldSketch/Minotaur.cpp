#include "Direction.h"
#include "Sprites.h"
#include "Logic.h"
#include "Unit.h"
#include "Minotaur.h"

Minotaur::Minotaur() :
    Unit(MINO_HITBOX_WALK_WIDTH, MINO_HITBOX_WALK_HEIGHT, MINO_HEALTH, MINO_SCORE, MINO_WALKING_WIDTH, MINO_INV_TIME),
    _attackArea(MINO_HITBOX_WALK_WIDTH, MINO_HITBOX_WALK_HEIGHT),
    _attack(&_attackArea, MINO_ATT_DAMAGE, MINO_ATT_FORCE, this) { }

void Minotaur::collideX() {
  _xVel = 0;
  if(_health != 0) {
    if(_isCharging) {
      _isCharging = false;
      _yVel -= MINO_ATT_FORCE;
    }
    if(!_heroDetected)
      toggleDir();
  }
}

boolean Minotaur::detect(Rect *heroHitbox, Logic *logic) {
  //int lineOfSight = _hitbox._y + _hitbox._height / 2,
  int lineOfSight = _hitbox._y,
      minoX = _hitbox._x,
      heroX = heroHitbox->_x;
  if(_dir == LEFT) {
    minoX += _hitbox._width - 1;
    heroX += heroHitbox->_width - 1;
  }
  int dist = (heroX - minoX),
      distDir = _dir * dist;
  if((distDir <= MINO_LOS + _hitbox._width - 1 &&
      distDir > -heroHitbox->_width &&
      heroHitbox->_y <= lineOfSight &&
      heroHitbox->_y + heroHitbox->_height > lineOfSight) ||
      _hitbox.contains(heroHitbox)) {
    char dir = getDirection(dist),
         tileY = worldToGrid(lineOfSight),
         tileXStart = worldToGrid(minoX) + dir,
         tileXEnd = worldToGrid(heroX) - dir;
    for(char tileX = tileXStart; dir * tileX <= dir * tileXEnd; tileX += dir)
      if(logic->tileIsSolid(tileX, tileY))
        return false;
    if(dist != 0)
      _dir = dir;
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
  Unit::initialize();
  newHandle(MINO_WALKING_HANDLE, MINO_WALKING_CELLS, MINO_FR_WALKING);
  _health = MINO_HEALTH;
  _heroDetected = false;
  _isCharging = false;
}

void Minotaur::updateAI(byte dTime, Logic *logic) { //dtime is still unused
  boolean grounded = logic->isGrounded(this);
  byte acc = 0;
  char targetSpeed = 0;
  if(_health != 0) {
    Rect *heroHitbox = &(logic->_hero->_hitbox);
    if(_isCharging || (grounded && detect(heroHitbox, logic))) { //Charge
      if(grounded)
        acc = MINO_ACC_CHARGE;
      targetSpeed = _dir * MINO_SPEED_CHARGE;
      //_hitbox._width = MINO_HITBOX_CHARGE_WIDTH;
      //_hitbox._height = MINO_HITBOX_CHARGE_HEIGHT;
      newHandle(MINO_CHARGING_HANDLE, MINO_CHARGING_CELLS, MINO_FR_CHARGING);
      _attackArea.setPos(_hitbox._x, _hitbox._y);
      logic->addAttack(&_attack);
    } else {
      newHandle(MINO_WALKING_HANDLE, MINO_WALKING_CELLS, MINO_FR_WALKING);
      //_hitbox._width = MINO_HITBOX_WALK_WIDTH;
      //_hitbox._height = MINO_HITBOX_WALK_HEIGHT;
      if(_heroDetected) { //Hunt
        int dist = heroHitbox->_x + heroHitbox->_width / 2 - _hitbox._x - _hitbox._width / 2;
        _dir = getDirection(dist);
        byte moveSpeed;
        if(grounded) {
          acc = MINO_ACC_HUNT;
          moveSpeed = MINO_SPEED_HUNT;
          if(heroHitbox->_y + heroHitbox->_height - 1 < _hitbox._y && _yVel == 0)
            _yVel = -MINO_JUMP;
        } else {
          acc = MINO_ACC_AIR;
          moveSpeed = max(MINO_SPEED_AIR, _dir * _xVel);
        }
        targetSpeed = _dir * min(moveSpeed, _dir * dist);
      } else { //Wander
        //_heroDetected = false;
        if(!logic->isWalkable(_hitbox._x + (1 + _dir) * _hitbox._width / 2, _hitbox._y + _hitbox._height))
          toggleDir();
        targetSpeed = _dir * MINO_SPEED_WALK;
        if(grounded)
          acc = MINO_ACC_WALK;
      }
    }
  } else { //Dying
    newHandle(MINO_DYING_HANDLE, MINO_DYING_CELLS, MINO_FR_DYING);
    _animLock = true;
    _animStop = true;
    if(grounded)
      acc = MINO_ACC_BRAKE;
  }
  _xVel = zoomIn(acc, _xVel, targetSpeed);
}
