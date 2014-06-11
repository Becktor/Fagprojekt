#include "Direction.h"
#include "Logic.h"
#include "Unit.h"
#include "Minotaur.h"
#include "Sprites.h"
#include "Scene.h"

Minotaur::Minotaur() : Unit(MINO_HITBOX_WIDTH, MINO_WALKING_HEIGHT, MINO_HEALTH, MINO_WALKING_WIDTH) {
  _detected  = false;
}

void Minotaur::collideX() {
  _xVel = 0;
  _charge = false;
  toggleDir();
}

void Minotaur::initialize() {
  Prop::initialize();
  _health = MINO_HEALTH;
}

void Minotaur::updateAI(int dTime, Logic *logic) { //dtime is still unused
  if(logic->isGrounded(this)) {
    if(!logic->isWalkable(_hitbox._x + (1 + _dir) * _hitbox._width / 2, _hitbox._y + _hitbox._height)){
      toggleDir();
      _charge = false;
    }
    if(!_charge) {
    }

    //detection
    Prop* hero = logic->getHero();
    _heroXpos = hero->_hitbox._x;
    _heroYpos = hero->_hitbox._y;
    _heroHeight = hero->_hitbox._height;
    _distDiff = _heroXpos - _hitbox._x;
    _distToHeroX = abs(_distDiff);
    _distToHeroY = abs(_heroYpos - _hitbox._y);
    _distance = sqrt((_distToHeroX * _distToHeroX) + (_distToHeroY * _distToHeroY));
    _minoMiddle = ((_hitbox._y + _hitbox._height- _hitbox._y)/10) + _hitbox._y;  //y-line which interesects with hero

    if (_distance > MINO_LOSE_HERO_DIST)
      _detected = false;
    if((_heroYpos + _heroHeight > _minoMiddle ) && (_minoMiddle > _heroYpos)) { //check hero in sight
      if((_distToHeroX <= MINO_SEE_HERO_DIST)){
        if(((_dir == RIGHT && _heroXpos > _hitbox._x) || (_dir== LEFT &&  _heroXpos < _hitbox._x))){ //Right direction?
          _detected = true;
          _charge = true;
          //Check the tiles in the horizontal sight
          char tileXend = worldToGrid(_heroXpos);
          char tileY = worldToGrid(_hitbox._y);
          for(char tileX = worldToGrid(_hitbox._x) + _dir; _dir * tileX < _dir * tileXend; tileX += _dir){
            byte tile = logic->_scene->getTile(tileX, tileY);
            if(getSolid(tile)){
              _detected = false;
              _charge = false;
            }
          }
        }
      }
    }
    if(_charge) {
      //Serial.println("Charge");
      _xVel = zoomIn(MINO_ACC_CHARGE, _xVel, _dir * MINO_SPEED_CHARGE);
      updateHandle(MINO_CHARGING_HANDLE, MINO_CHARGING_CELLS, MINO_CHARGING_FR);
    } else {
      updateHandle(MINO_WALKING_HANDLE, MINO_WALKING_CELLS, MINO_WALKING_FR);
      _xVel = zoomIn(MINO_ACC_WALK, _xVel, _dir * MINO_SPEED_WALK);
    }
  }
}
