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
  _attackSound = false;
  _isAttacking = true;
  _isDucking = true;
  _isJumping = false;
}

void Hero::updateAI(int dTime, Logic *logic) { //dtime is still unused
  //Hero x-movement
  char nunchukX = _nunchuk->analogX - NUNCHUK_MIDDLE,
       nunchukDir = getDirection(nunchukX),
       nunchukXAbs = nunchukX * nunchukDir;
  if(nunchukXAbs >= NUNCHUK_WALK) {
    byte FR;
    if(nunchukXAbs >= NUNCHUK_RUN) {
      FR = HERO_RUNNING_FR;
      _xVel = HERO_SPEED_RUN;
    } else {
      FR = HERO_WALKING_FR;
      _xVel = HERO_SPEED_WALK;
    }
    updateHandle(HERO_MOVING_HANDLE, HERO_MOVING_CELLS, FR);
    _dir = nunchukDir;
    _xVel = _xVel * nunchukDir;
  } else { //IDLE
    _xVel = 0;
    updateHandle(HERO_IDLE_HANDLE, HERO_IDLE_CELLS, HERO_IDLE_FR);
  }

  //Hero jump
  if(logic->isGrounded(this)) {
    if(_nunchuk->cButton) {
      if(!_isJumping) {
        _yVel -= HERO_SPEED_JUMP;
        _isJumping = true;
      }
    } else
      _isJumping = false;
  }

  //Hero duck
  if(NUNCHUK_DUCK > _nunchuk->analogY && !_isJumping) {
    updateHandle(HERO_DUCKING_HANDLE, HERO_DUCKING_CELLS, HERO_DUCKING_FR);
    if(!_isDucking) {
      _hitbox._height = HERO_HEIGHT_DUCK;
      _hitbox._y += HERO_HEIGHT_STAND - HERO_HEIGHT_DUCK;
      _isDucking = true;
    }
  } else if(_isDucking) {
    _hitbox._height = HERO_HEIGHT_STAND;
    _hitbox._y += HERO_HEIGHT_DUCK - HERO_HEIGHT_STAND;
    _isDucking = false;
  }

  //Hero action
  if(_nunchuk->zButton) {
    if(_isDucking && logic->atExit(this)) {
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
      _attack._force = _dir * HERO_ATT_FORCE;
      logic->addAttack(&_attack);
    } else 
      _attackSound = false;
  } else
    _isAttacking = false;
}

boolean Hero::getAttackSound() {
  return _attackSound;
}
