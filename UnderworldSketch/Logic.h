#ifndef logic_h
#define logic_h

#include <Arduino.h>
#include <LinkedList.h>
#include "Tiles.h"
#include "Attack.h"
#include "Unit.h"
#include "Scene.h"

const static short GRAVITY = 1;

class Scene;
class Unit;
class Logic
{
  private:
    boolean _gameOver, _heroWin, _hasAttack;
    Scene *_scene;
    LinkedList<Attack*> _attacks;
    Unit *_hero;
  public:
    Logic(Scene *scene);
    void addAttack(int x, int y, int width, int height, int damage, Unit *owner);
    boolean atExit(Unit *unit);
    void executeAttacks();
    void coinCol();
    Unit* getHero();
    void gravitate(Unit *unit, int dTime);
    boolean isGameOver();
    boolean isGrounded(Unit *unit);
    boolean isHeroWin();
    boolean isSolid(int x, int y);
    boolean moveUnitHoriz(Unit *unit, int dX);
    boolean moveUnitVerti(Unit *unit, int dY);
    void restartGame();
    void setGameOver(boolean gameOver, boolean heroWon);
    void setHero(Unit *hero);
};
#endif

