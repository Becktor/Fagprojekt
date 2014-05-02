#ifndef logic_h
#define logic_h

#include <Arduino.h>
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
  public:
    Logic(Scene *scene);
    void gravitate(Unit *unit, int dTime);
    boolean isGameOver();
    boolean isHeroWin();
    boolean moveUnitHoriz(Unit *unit, int dX);
    boolean moveUnitVerti(Unit *unit, int dY);
    boolean isGrounded(Unit *unit);
    boolean isSolid(int x, int y);
    void restartGame();
    void setGameOver(boolean gameOver);
};
#endif
