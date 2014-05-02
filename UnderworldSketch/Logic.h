#ifndef logic_h
#define logic_h

#include <Arduino.h>
#include <LinkedList.h>
#include "Tiles.h"
#include "Unit.h"
#include "Scene.h"

const static short GRAVITY = 1;

class Unit;
class Logic
{
  private:
    boolean _gameOver, _heroWin;
    Scene *_scene;
    LinkedList<Unit*> *_units;
    Unit *_hero;
  public:
    Logic(Scene *scene);
    Unit* getHero();
    void gravitate(Unit *unit, int dTime);
    boolean isGameOver();
    boolean isGrounded(Unit *unit);
    boolean isHeroWin();
    boolean isSolid(int x, int y);
    boolean moveUnitHoriz(Unit *unit, int dX);
    boolean moveUnitVerti(Unit *unit, int dY);
    void restartGame();
    void setGameOver(boolean gameOver);
    void setHero(Unit *hero);
    void setUnits(LinkedList<Unit*> *units);
};
#endif
