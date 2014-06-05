#include "Geo.h"
#include "Logic.h"
//#include "Prop.h"
#include "Unit.h"
#include "Hero.h"


Hero::Hero(int x, int y, ArduinoNunchuk* nunchuk) : Unit(x, y, HERO_WIDTH, HERO_HEIGHT_STAND, HERO_HEALTH),
                                                    _attackArea(0, 0, HERO_ATT_RANGE, HERO_HEIGHT_STAND),
                                                   _attack(&_attackArea, HERO_ATT_DAMAGE, HERO_ATT_FORCE, this) {
  _nunchuk = nunchuk;
}

void Hero::updateAI(int dTime, Logic *logic) { //dtime is still unused
  Rect* hitbox = getHitbox();

  //Hero x-movement
  if((130 < _nunchuk->analogX) && (_nunchuk->analogX < 160)){
    setXVel(HERO_SPEED_WALK);
    setDir(RIGHT);  
  }
  else if(_nunchuk->analogX > 160){
    setXVel(HERO_SPEED_RUN);
    setDir(RIGHT); 
  }
  else if((80 < _nunchuk->analogX) && (_nunchuk->analogX < 110)){
    setXVel(-HERO_SPEED_WALK);
    setDir(LEFT);
  }
  else if((15 < _nunchuk->analogX) && (_nunchuk->analogX < 80)){
    setXVel(-HERO_SPEED_RUN);
    setDir(LEFT);
  }
  else 
    setXVel(0);

  //Hero duck - If analogX is lower than 90
  if(45 > _nunchuk -> analogY) {
    if(!_isDucking) {
      hitbox->setHeight(HERO_HEIGHT_DUCK);
      hitbox-> translate(0, HERO_HEIGHT_STAND - HERO_HEIGHT_DUCK);
      _isDucking = true;
    }
  } else if(_isDucking) {
    hitbox->setHeight(HERO_HEIGHT_STAND);
    hitbox->translate(0, HERO_HEIGHT_DUCK - HERO_HEIGHT_STAND);
    _isDucking = false;
  }

  //Hero jump
  if(logic->isGrounded(this)) {
    if(_nunchuk->cButton) {
      if(!_isJumping) {
        setYVel(-HERO_SPEED_JUMP);
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
      int attackX = hitbox->getX();
      if(getDir() == LEFT)
        attackX -= HERO_ATT_RANGE;
      else
        attackX += hitbox->getWidth();
      _attackArea.setPos(attackX, hitbox->getY());
      _attackArea.setHeight(hitbox->getHeight());
      _attack._force = HERO_ATT_FORCE * getDir();
      logic->addAttack(&_attack);
    } else 
      _attackSound = false;
  } else
    _isAttacking = false;
}

boolean Hero::getAttackSound(){
  return _attackSound;
}
