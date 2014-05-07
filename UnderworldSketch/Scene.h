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
#include "Tiles.h"
#include "Module.h"
#include "Unit.h"
#include "Prop.h"

const static short
    TILE_SIZE = 48, //One tile unit to world units conv.
    XMODULES = 4,
    YMODULES = 4,
    SCENE_WIDTH = XMODULES * (MODULE_WIDTH - 1) - 1,
    SCENE_HEIGHT = YMODULES * (MODULE_HEIGHT - 1) - 1;

class Unit;
class Scene
{
  private:
    Tiles _tiles[SCENE_WIDTH][SCENE_HEIGHT];
    LinkedList<Unit*> _units;
    LinkedList<Prop*> _props;
  public:
    Scene();
    void addUnit(Unit *unit, Point *point);
    void addProp(Prop *prop, Point *point);
    void clearUnits();
    boolean contains(int x, int y);
    int getWidth();
    int getHeight();
    Tiles getTile(int x, int y);
    LinkedList<Unit*>* getUnits();
    LinkedList<Prop*>* getProps();
    void setTile(int x, int y, Tiles tile);
};

#endif
