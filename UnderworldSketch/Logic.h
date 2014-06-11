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
    LinkedList<Attack*> _attacks;
    Prop *_hero;
  public:
    Scene *_scene;
    boolean _gameOver, _heroWin, _hasAttack;
    int _score;
    Logic(Scene *scene);
    void addAttack(Attack* attack);
    boolean atExit(Prop *prop);
    void clearAttacks();
    boolean coinCol(Prop *prop);
    void executeAttacks(Prop* prop);
    Prop* getHero();
    boolean isGrounded(Prop *prop);
    boolean isWalkable(int x, int y);
    boolean movePropHoriz(Prop *prop, int dX);
    boolean movePropVerti(Prop *prop, int dY);
    void setHero(Prop *hero);
    void updatePhysics(Prop* prop, int dTime);
};
#endif
