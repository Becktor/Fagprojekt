/*
 *  Contains all physics functions, and functions which the AI would need.
 */

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
    LinkedList<Attack*> _attacks; //Current active attacks
  public:
    boolean _gameOver, _heroWin; //Whether the round is over, and whether the hero won.
    Prop *_hero; //Is a prop to avoid circular references.
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
    boolean tileIsSolid(byte x, byte y);
    void updatePhysics(byte dTime, Prop* prop);
};
#endif
