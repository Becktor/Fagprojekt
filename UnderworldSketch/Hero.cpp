#include "Direction.h"
#include "Geo.h"
#include "Attack.h"
#include "Logic.h"
#include "Unit.h"
#include "Hero.h"

Hero::Hero(ArduinoNunchuk* nunchuk) : Unit(HERO_WIDTH, HERO_HEIGHT_STAND, HERO_HEALTH, HERO_IMAGE_WIDTH),
                                      _attackArea(HERO_ATT_RANGE, HERO_HEIGHT_STAND),
                                      _attack(&_attackArea, HERO_ATT_DAMAGE, HERO_ATT_FORCE, this) {
  _nunchuk = nunchuk;
}

void Hero::updateAI(int dTime, Logic *logic) { //dtime is still unused
    _handle = HERO_IDLE_HANDLE;
    _cells = HERO_IDLE_CELLS;

  //Hero x-movement
  if((130 < _nunchuk->analogX) && (_nunchuk->analogX < 160)){
    _xVel = HERO_SPEED_WALK;
    if(_handle != HERO_WALKING_HANDLE)
    {
      _handle = HERO_WALKING_HANDLE;
      _cells = HERO_WALKING_CELLS;
      _currentCell = 0;
    }
    setFR(HERO_WALKING_FR);
    _dir = RIGHT;  
  }
  else if(_nunchuk->analogX > 160){
    _xVel = HERO_SPEED_RUN;
    if(_handle != HERO_WALKING_HANDLE)
    {
      _handle = HERO_WALKING_HANDLE;
      _cells = HERO_WALKING_CELLS;
      _currentCell = 0;
    }
    setFR(HERO_RUNNING_FR);
    _dir = RIGHT;  
  }
  else if((80 < _nunchuk->analogX) && (_nunchuk->analogX < 110)){
    _xVel = -HERO_SPEED_WALK;
    if(_handle != HERO_WALKING_HANDLE)
    {
      _handle = HERO_WALKING_HANDLE;
      _cells = HERO_WALKING_CELLS;
      _currentCell = 0;
    }
    setFR(HERO_WALKING_FR);
    _dir = LEFT;  
  }
  else if((15 < _nunchuk->analogX) && (_nunchuk->analogX < 80)){
    _xVel = -HERO_SPEED_RUN;
    if(_handle != HERO_WALKING_HANDLE)
    {
      _handle = HERO_WALKING_HANDLE;
      _cells = HERO_WALKING_CELLS;
      _currentCell = 0;
    }
    setFR(HERO_RUNNING_FR);
    _dir = LEFT;
  }
  else 
  {
    if(_handle != HERO_IDLE_HANDLE)
    {
      _handle = HERO_IDLE_HANDLE;
      _cells = HERO_IDLE_CELLS;
      _currentCell = 0;
      setFR(HERO_IDLE_FR);
      _xVel = 0;
    }
  }

  //Hero duck - If analogX is lower than 90
  if(45 > _nunchuk -> analogY) {
    if(!_isDucking) {
      if(_handle != HERO_DUCKING_HANDLE)
      {
      _handle = HERO_DUCKING_HANDLE;
      _cells = HERO_DUCKING_CELLS;
      _currentCell = 0;
      setFR(HERO_DUCKING_FR);
      }
      _hitbox._height = HERO_HEIGHT_DUCK;
      _hitbox._y += HERO_HEIGHT_STAND - HERO_HEIGHT_DUCK;
      //_hitbox.translate(0, HERO_HEIGHT_STAND - HERO_HEIGHT_DUCK);
      _isDucking = true;
    }
  } else if(_isDucking) {
    _hitbox._height = HERO_HEIGHT_STAND;
    _hitbox._y += HERO_HEIGHT_DUCK - HERO_HEIGHT_STAND;
    //_hitbox.translate(0, HERO_HEIGHT_DUCK - HERO_HEIGHT_STAND);
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

boolean Hero::getAttackSound(){
  return _attackSound;
}

