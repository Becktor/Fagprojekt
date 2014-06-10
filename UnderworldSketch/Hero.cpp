#include "Direction.h"
#include "Geo.h"
#include "Attack.h"
#include "Logic.h"
#include "Unit.h"
#include "Hero.h"

Hero::Hero(ArduinoNunchuk* nunchuk) : Unit(HERO_WIDTH, HERO_HEIGHT_STAND, HERO_HEALTH, HERO_IMAGE_WIDTH),
                                      _attackArea(0, 0, HERO_ATT_RANGE, HERO_HEIGHT_STAND),
                                      _attack(&_attackArea, HERO_ATT_DAMAGE, HERO_ATT_FORCE, this) {
  _nunchuk = nunchuk;
}

void Hero::updateAI(int dTime, Logic *logic) { //dtime is still unused
    

  //Hero x-movement
  if((130 < _nunchuk->analogX) && (_nunchuk->analogX < 160)){
    _xVel = HERO_SPEED_WALK;
    
    if(getHandle() != HERO_WALKING_HANDLE)
    {
      setHandle(HERO_WALKING_HANDLE);
      setCells(HERO_WALKING_CELLS);
      setCurrentCell(0);
    }
    setFR(HERO_WALKING_FR);
    setDir(RIGHT);  
  }
  else if(_nunchuk->analogX > 160){
    _xVel = HERO_SPEED_RUN;
    if(getHandle() != HERO_WALKING_HANDLE)
    {
      setHandle(HERO_WALKING_HANDLE);
      setCells(HERO_WALKING_CELLS);
      setCurrentCell(0);
    }
    setFR(HERO_RUNNING_FR);
    setDir(RIGHT); 
  }
  else if((80 < _nunchuk->analogX) && (_nunchuk->analogX < 110)){
    _xVel = -HERO_SPEED_WALK;
    if(getHandle() != HERO_WALKING_HANDLE)
    {
      setHandle(HERO_WALKING_HANDLE);
      setCells(HERO_WALKING_CELLS);
      setCurrentCell(0);
    }
    setFR(HERO_WALKING_FR);
    setDir(LEFT);
  }
  else if((15 < _nunchuk->analogX) && (_nunchuk->analogX < 80)){
    _xVel = -HERO_SPEED_RUN;
    if(getHandle() != HERO_WALKING_HANDLE)
    {
      setHandle(HERO_WALKING_HANDLE);
      setCells(HERO_WALKING_CELLS);
      setCurrentCell(0);
    }
    setFR(HERO_RUNNING_FR);
    setDir(LEFT);
  }
  else 
  {
    if(getHandle() != HERO_IDLE_HANDLE)
    {
      setHandle(HERO_IDLE_HANDLE);
      setCells(HERO_IDLE_CELLS);
      setCurrentCell(0);
      setFR(HERO_IDLE_FR);
      _xVel = 0;
    }
  }

  //Hero duck - If analogX is lower than 90
  if(45 > _nunchuk -> analogY) {
    if(!_isDucking) {
      if(getHandle() != HERO_IDLE_HANDLE)
      {
      setHandle(HERO_DUCKING_HANDLE);
      setCells(HERO_DUCKING_CELLS);
      setCurrentCell(0);
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
      logic->setGameOver(true, true);
    } else if(!_isAttacking) {
      //Attack
      _isAttacking = true;
      _attackSound = true;
      char dir = getDir();
      if(dir == LEFT)
        _attackArea._x = _hitbox._x - HERO_ATT_RANGE;
      else
        _attackArea._x = _hitbox._x + _hitbox._width;
      _attackArea._y = _hitbox._y;
      _attackArea._height = _hitbox._height;
      _attack._force = HERO_ATT_FORCE * dir;
      logic->addAttack(&_attack);
    } else 
      _attackSound = false;
  } else
    _isAttacking = false;
}

boolean Hero::getAttackSound(){
  return _attackSound;
}

