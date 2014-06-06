#ifndef logic_h
#define logic_h

#include <Arduino.h>
#include <LinkedList.h>
#include "Tiles.h"
#include "Geo.h"
#include "Prop.h"
#include "Attack.h"
#include "Scene.h"

const static byte GRAVITY = 1;

class Logic {
  private:
    boolean _gameOver, _heroWin, _hasAttack;
    Scene *_scene;
    LinkedList<Attack*> _attacks;
    Prop *_hero;
  public:
    int _score;
    Logic(Scene *scene);
    void addAttack(Attack* attack);
    boolean atExit(Prop *prop);
    void clearAttacks();
    void coinCol();
    void executeAttacks(Prop* prop);
    Prop* getHero();
    void gravitate(Prop *prop, int dTime);
    boolean isGameOver();
    boolean isGrounded(Prop *prop);
    boolean isHeroWin();
    boolean isSolid(int x, int y);
    boolean movePropHoriz(Prop *prop, int dX);
    boolean movePropVerti(Prop *prop, int dY);
    void restartGame();
    void setGameOver(boolean gameOver, boolean heroWon);
    void setHero(Prop *hero);
    void updatePhysics(Prop* prop, int dTime);
};
#endif
