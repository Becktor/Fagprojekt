#include "Direction.h"
#include "Geo.h"
#include "Attack.h"
#include "Logic.h"
#include "Unit.h"
#include "Hero.h"
#include "Sprites.h"

Hero::Hero(ArduinoNunchuk* nunchuk) : 
    Unit(HERO_HITBOX_WIDTH, HERO_HITBOX_HEIGHT_STAND, HERO_HEALTH, 0, HERO_IDLE_WIDTH, HERO_IDLE_HEIGHT, HERO_INV_TIME),
    _attackArea(HERO_ATT_RANGE, HERO_HITBOX_HEIGHT_STAND),
    _attack(&_attackArea, HERO_ATT_DAMAGE, HERO_ATT_FORCE, this) {
  _nunchuk = nunchuk;
}

//Hit function.
//Called when attacked, if not invulnerable.
void Hero::hit(byte damage, char force) {
  Unit::hit(damage, force);
  push(force);
}

//Initialize function.
//Called when used in a new map.
void Hero::initialize() {
  Unit::initialize();
  newHandle(HERO_IDLE_HANDLE, HERO_IDLE_CELLS, HERO_FR_IDLE);
  _health = HERO_HEALTH;
  _attackSound = false;
  _isAttacking = true;
  _isDucking = true;
  _isJumping = false;
}

//AI update function. Evaluates player input.
void Hero::updateAI(byte dTime, Logic *logic) { //dtime is still unused
  //Hero x-movement
  char nunchukX = _nunchuk->analogX - NUNCHUK_REST_X,
  nunchukDir = getDirection(nunchukX),
  nunchukXAbs = nunchukX * nunchukDir,
  acc,
  targetSpeed;
  
  //Checks if the hero is grounded
  if(logic->isGrounded(this)) {
    if(NUNCHUK_DUCK > _nunchuk->analogY && !_isJumping) {
      //DUCK
      if(_nunchuk->analogY <= 30){
        targetSpeed = 0;
        newHandle(HERO_DUCK_HANDLE, 1, 1000);  
      } else {
        acc = HERO_ACC_DUCK;
        targetSpeed = HERO_SPEED_DUCK;
        newHandle(HERO_DUCK_HANDLE, HERO_DUCK_CELLS, HERO_FR_DUCKING);
      }
      if(!_isDucking) {
        _hitbox._height = HERO_HITBOX_HEIGHT_DUCK;
        _hitbox._y += HERO_HITBOX_HEIGHT_STAND - HERO_HITBOX_HEIGHT_DUCK;
        _isDucking = true;
      }
       _dir = nunchukDir;
    } else if(_isDucking) {
      _hitbox._height = HERO_HITBOX_HEIGHT_STAND;
      _hitbox._y += HERO_HITBOX_HEIGHT_DUCK - HERO_HITBOX_HEIGHT_STAND;
      _isDucking = false;
    } else if(nunchukXAbs >= NUNCHUK_WALK){
      byte FR;
      //Checks if the hero should walk or run
      if(nunchukXAbs >= NUNCHUK_RUN) {
        //RUN
        acc = HERO_ACC_RUN;
        targetSpeed = HERO_SPEED_RUN;
        FR = HERO_FR_RUNNING;
      } else {
        //WALK
        acc = HERO_ACC_WALK;
        targetSpeed = HERO_SPEED_WALK;
        FR = HERO_FR_WALKING;
      }
      //Walking and Running use the same handle, but different frame rates
      newHandle(HERO_MOVE_HANDLE, HERO_MOVE_CELLS, FR);
    } else {
      //IDLE
      acc = HERO_ACC_WALK;
      targetSpeed = 0;
      nunchukDir = 0;
      newHandle(HERO_IDLE_HANDLE, HERO_IDLE_CELLS, HERO_FR_IDLE);
    }
    //JUMP
    if(_nunchuk->cButton) {
      if(!_isJumping) {
        //Starts a jump
        _yVel = -HERO_JUMP;
        _isJumping = true;
        GD.sample(JUMP, JUMP_LENGTH, 8000, ADPCM_SAMPLES);
      }
    }
    else //player isn't able to continuously jump by holding the jump button down
      _isJumping = false;
  } else {
    //AIR
    acc = HERO_ACC_AIR;
    targetSpeed = max(HERO_SPEED_AIR, nunchukDir * _xVel);
    if(_yVel <= 0)
      newHandle(HERO_JUMP_HANDLE, HERO_JUMP_CELLS, HERO_FR_JUMP);
    else
      newHandle(HERO_FALL_HANDLE, HERO_FALL_CELLS, HERO_FR_FALL);
  }
  if(nunchukXAbs >= NUNCHUK_WALK){
    targetSpeed = targetSpeed * nunchukDir;
    _dir = nunchukDir;
  } else
    targetSpeed = 0;
  _xVel = zoomIn(acc, _xVel, targetSpeed); //Move

  //Hero action
  _attackSound = false;
  if(_nunchuk->zButton) {
    if(_isDucking && logic->atExit(this)) {
      //EXIT
      logic->_gameOver = true;
      logic->_heroWin = true;
    } 
    else if(!_isAttacking && !_isDucking) {
      //ATTACK
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

