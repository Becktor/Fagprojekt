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

const static byte
    TILE_SIZE = 48, //One tile unit to world units conv.
    XMODULES = 4,
    YMODULES = 4,
    SCENE_WIDTH = XMODULES * (MODULE_WIDTH - 1) - 1,
    SCENE_HEIGHT = YMODULES * (MODULE_HEIGHT - 1) - 1,
    MINOTAURS = 10;

char worldToGrid(int x);
int gridToWorld(char x);

class Unit;
class Minotaur;
class Scene {
  private:
    byte _tiles[SCENE_WIDTH][SCENE_HEIGHT], _minoIndex;
    Minotaur* _minotaurs[10];
    LinkedList<Prop*> _props;
    LinkedList<Unit*> _units;
  public:
    Scene();
    void addMinotaur(char x, char y);
    void addProp(Prop *prop, char x, char y);
    void addUnit(Unit *unit, char x, char y);
    void clearUnits();
    boolean contains(char x, char y);
    byte getWidth();
    byte getHeight();
    byte getTile(char x, char y);
    LinkedList<Unit*> *getUnits();
    LinkedList<Prop*> *getProps();
    void moveProp(Prop *prop, char x, char y);
    void setTile(char x, char y, byte tile);
};
#endif
