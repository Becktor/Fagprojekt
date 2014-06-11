#include "Direction.h"
#include "Geo.h"
#include "Attack.h"
#include "Logic.h"
#include "Unit.h"
#include "Hero.h"
#include "Sprites.h"

Hero::Hero(ArduinoNunchuk* nunchuk) : Unit(HERO_HITBOX_WIDTH, HERO_HEIGHT_STAND, HERO_HEALTH, HERO_IDLE_WIDTH),
                                      _attackArea(HERO_ATT_RANGE, HERO_HEIGHT_STAND),
                                      _attack(&_attackArea, HERO_ATT_DAMAGE, HERO_ATT_FORCE, this) {
  _nunchuk = nunchuk;
}

void Hero::initialize() {
  Prop::initialize();
  _health = HERO_HEALTH;
}

void Hero::updateAI(int dTime, Logic *logic) { //dtime is still unused
  //Hero x-movement
  char nunchukX = _nunchuk->analogX - NUNCHUK_MIDDLE,
       nunchukDir = getDirection(nunchukX),
       nunchukXAbs = nunchukX * nunchukDir;
  if(nunchukXAbs >= NUNCHUK_WALK) {
    if(_handle != HERO_MOVING_HANDLE)
      updateHandle(HERO_MOVING_HANDLE, HERO_MOVING_CELLS);
    if(nunchukXAbs >= NUNCHUK_RUN) {
      _FR = HERO_RUNNING_FR;
      _xVel = HERO_SPEED_RUN;
    } else {
      _FR = HERO_WALKING_FR;
      _xVel = HERO_SPEED_WALK;
    }
    _dir = nunchukDir;
    _xVel = _xVel * nunchukDir;
  } else { //IDLE
    _FR = HERO_IDLE_FR;
    _xVel = 0;
    if(_handle != HERO_IDLE_HANDLE)
      updateHandle(HERO_IDLE_HANDLE, HERO_IDLE_CELLS);
  }

  //Hero duck - If analogX is lower than 90
  if(NUNCHUK_DUCK > _nunchuk->analogY) {
    if(_handle != HERO_IDLE_HANDLE) {
      updateHandle(HERO_DUCKING_HANDLE, HERO_DUCKING_CELLS);
      _FR = HERO_DUCKING_FR;
    }
    if(!_isDucking) {
      _hitbox._height = HERO_HEIGHT_DUCK;
      _hitbox._y += HERO_HEIGHT_STAND - HERO_HEIGHT_DUCK;
      _isDucking = true;
    }
  } else if(_isDucking) {
    _hitbox._height = HERO_HEIGHT_STAND;
    _hitbox._y += HERO_HEIGHT_DUCK - HERO_HEIGHT_STAND;
    updateHandle(HERO_DUCKING_HANDLE, HERO_DUCKING_CELLS);
    _FR = HERO_DUCKING_FR;
    _isDucking = false;
  }

  //Hero jump
  if(logic->isGrounded(this)) {
    if(_nunchuk->cButton) {
      if(!_isJumping) {
        _yVel = -HERO_SPEED_JUMP;
        _isJumping = true;
      }
    } else
      _isJumping = false;
  }

  //Hero action
  if(_nunchuk->zButton) {
    if(_isDucking && logic->atExit(this)) {
      //Map exit
      _isAttacking = true;
      logic->_gameOver = true;
      logic->_heroWin = true;
    } else if(!_isAttacking) {
      //Attack
      _isAttacking = true;
      _attackSound = true;
      if(_dir == LEFT)
        _attackArea._x = _hitbox._x - HERO_ATT_RANGE;
      else
        _attackArea._x = _hitbox._x + _hitbox._width;
      _attackArea._y = _hitbox._y;
      _attackArea._height = _hitbox._height;
      _attack._force = HERO_ATT_FORCE * _dir;
      logic->addAttack(&_attack);
    } else 
      _attackSound = false;
  } else
    _isAttacking = false;
}

boolean Hero::getAttackSound() {
  return _attackSound;
}
