/*
 *  Scenes holds map information and functions
 *  handling basic collision data.
 *  The scenes are limited to a specific height
 *  and width. This is because the _map variable
 *  would have to be a pointer if it were not,
 *  making any array functions difficult. This
 *  could be changed if figured out and
 *  necessary
 */

#ifndef scene_h
#define scene_h

#include <Arduino.h>
#include <LinkedList.h>
#include "Tiles.h"
#include "Module.h"
#include "Prop.h"
#include "Coin.h"

const static byte
    TILE_SIZE = 48, //One tile unit to world units conv.
    XMODULES = 4,
    YMODULES = 4,
    SCENE_WIDTH = XMODULES * (MODULE_WIDTH - 1) - 1,
    SCENE_HEIGHT = YMODULES * (MODULE_HEIGHT - 1) - 1,
    MINOTAURS = 10,
    COINS = 5;

char worldToGrid(int x);
int gridToWorld(byte x);

class Unit;
class Minotaur;
class Scene {
  private:
    byte _tiles[SCENE_WIDTH][SCENE_HEIGHT], _minoIndex, _coinIndex;
    Minotaur* _minotaurs[MINOTAURS];
    Coin* _coins[COINS];
    //Prop** _test[2];
  public:
    LinkedList<Coin*> _coinList;
    LinkedList<Unit*> _unitList;

    Scene();
    void addCoin(byte x, byte y);
    void addMinotaur(byte x, byte y);
    void addUnit(Unit* unit, byte x, byte y);
    void clearProps();
    boolean contains(byte x, byte y);
    byte getWidth();
    byte getHeight();
    LinkedList<Coin*>* getCoins();
    LinkedList<Unit*>* getUnits();
    byte getTile(byte x, byte y);
    void setProp(Prop *prop, byte x, byte y);
    void setTile(byte x, byte y, byte tile);
};
#endif
