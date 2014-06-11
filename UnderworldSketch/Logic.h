#ifndef logic_h
#define logic_h

#include <Arduino.h>
#include <LinkedList.h>
#include "Tiles.h"
#include "Geo.h"
#include "Prop.h"
#include "Coin.h"
#include "Attack.h"
#include "Scene.h"

const static byte GRAVITY = 1;

class Logic {
  private:
    LinkedList<Attack*> _attacks;
  public:
    boolean _gameOver, _heroWin, _hasAttack;
    Prop *_hero;
    Scene *_scene;

    Logic(Scene *scene);
    void addAttack(Attack* attack);
    boolean atExit(Prop *prop);
    void clearAttacks();
    boolean coinCollision(Coin *coin);
    void executeAttacks(Prop* prop);
    boolean isGrounded(Prop *prop);
    boolean isWalkable(int x, int y);
    boolean movePropHoriz(Prop *prop, int dX);
    boolean movePropVerti(Prop *prop, int dY);
    void updatePhysics(Prop* prop, int dTime);
};
#endif
