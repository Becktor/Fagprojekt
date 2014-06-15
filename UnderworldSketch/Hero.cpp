#include "Direction.h"
#include "Geo.h"
#include "Attack.h"
#include "Logic.h"
#include "Unit.h"
#include "Hero.h"
#include "Sprites.h"

Hero::Hero(ArduinoNunchuk* nunchuk) : 
    Unit(HERO_HITBOX_WIDTH, HERO_HITBOX_HEIGHT_STAND, HERO_HEALTH, 0, HERO_IDLE_WIDTH, HERO_INV_TIME),
    _attackArea(HERO_ATT_RANGE, HERO_HITBOX_HEIGHT_STAND),
    _attack(&_attackArea, HERO_ATT_DAMAGE, HERO_ATT_FORCE, this) {
  _nunchuk = nunchuk;
}

void Hero::initialize() {
  Unit::initialize();
  newHandle(HERO_IDLE_HANDLE, HERO_IDLE_CELLS, HERO_FR_IDLE);
  _health = HERO_HEALTH;
  _attackSound = false;
  _isAttacking = true;
  _isDucking = true;
  _isJumping = false;
}

void Hero::updateAI(byte dTime, Logic *logic) { //dtime is still unused
  //Hero x-movement
  char nunchukX = _nunchuk->analogX - NUNCHUK_REST_X,
  nunchukDir = getDirection(nunchukX),
  nunchukXAbs = nunchukX * nunchukDir,
  acc,
  targetSpeed;
  if(logic->isGrounded(this)) {
    //Hero duck
    if(NUNCHUK_DUCK > _nunchuk->analogY && !_isJumping) {
      acc = HERO_ACC_DUCK;
      targetSpeed = nunchukDir * HERO_SPEED_DUCK;
      newHandle(HERO_DUCK_HANDLE, HERO_DUCK_CELLS, HERO_FR_DUCKING);
      if(!_isDucking) {
        _hitbox._height = HERO_HITBOX_HEIGHT_DUCK;
        _hitbox._y += HERO_HITBOX_HEIGHT_STAND - HERO_HITBOX_HEIGHT_DUCK;
        _isDucking = true;
      }
    } 
    else if(_isDucking) {
      _hitbox._height = HERO_HITBOX_HEIGHT_STAND;
      _hitbox._y += HERO_HITBOX_HEIGHT_DUCK - HERO_HITBOX_HEIGHT_STAND;
      _isDucking = false;

    } 
    else if(nunchukXAbs >= NUNCHUK_WALK){
      byte FR;
      if(nunchukXAbs >= NUNCHUK_RUN) {
        acc = HERO_ACC_RUN;
        targetSpeed = HERO_SPEED_RUN;
        FR = HERO_FR_RUNNING;
      } 
      else {
        acc = HERO_ACC_WALK;
        targetSpeed = HERO_SPEED_WALK;
        FR = HERO_FR_WALKING;
      }
      newHandle(HERO_MOVE_HANDLE, HERO_MOVE_CELLS, FR);
      _dir = nunchukDir;
      targetSpeed = nunchukDir * targetSpeed;
    }
    else {
      acc = HERO_ACC_WALK;
      targetSpeed = 0;
      nunchukDir = 0;
      newHandle(HERO_IDLE_HANDLE, HERO_IDLE_CELLS, HERO_FR_IDLE);
    }

    if(_nunchuk->cButton) {
      if(!_isJumping) {
        _yVel = -HERO_JUMP;
        _isJumping = true;
        GD.sample(JUMP, JUMP_LENGTH, 8000, ADPCM_SAMPLES);
      }
    } 
    else
      _isJumping = false;

  } 
  else {
    if(_yVel <= 0)
      newHandle(HERO_JUMP_HANDLE, HERO_JUMP_CELLS, HERO_FR_JUMP);
    else
      newHandle(HERO_FALL_HANDLE, HERO_FALL_CELLS, HERO_FR_FALL);
    if(nunchukXAbs >= NUNCHUK_RUN)
      targetSpeed = nunchukDir * HERO_SPEED_AIR;
    else
      targetSpeed =  0;
    if(HERO_SPEED_AIR > nunchukDir * _xVel)
      acc = HERO_ACC_AIR;
    else
      acc = 0;
  }

  _xVel = zoomIn(acc, _xVel, targetSpeed);

  //Hero action
  _attackSound = false;
  if(_nunchuk->zButton) {
    if(_isDucking && logic->atExit(this)) {
      logic->_gameOver = true;
      logic->_heroWin = true;
    } 
    else if(!_isAttacking && !_isDucking) {
      //Attack
      _isAttacking = true;
      _attackArea._width = HERO_ATT_RANGE + _hitbox._width;
      _attackArea._x = _hitbox._x;
      if(_dir == LEFT)
        _attackArea._x -= HERO_ATT_RANGE;
      _attackArea._y = _hitbox._y;
      _attack._force = _dir * HERO_ATT_FORCE;
      logic->addAttack(&_attack);
      newHandle(HERO_ATTACK_HANDLE, HERO_ATTACK_CELLS, HERO_FR_ATTACKING);
      _animLock = true;
      _attackSound = true;
    }
  } 
  else
    _isAttacking = false;
}

boolean Hero::getAttackSound() {
  return _attackSound;
}

