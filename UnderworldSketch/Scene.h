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

#include "Arduino.h"
#include "Geo.h"

const int SCENE_WIDTH = 25;
const int SCENE_HEIGHT = 25;
const int TILE_SIZE = 48; //One tile unit to world units conv.

enum Tiles{
  Rock,
  Spikes,
  Wall
};

class Scene
{
  private:
    Tiles _map[SCENE_WIDTH][SCENE_HEIGHT];

  public:
    Scene();
    int getWidth();
    int getHeight();
    boolean isSolid(Point p);
    void setTile(int x, int y, Tiles tile);
    void setTile(Point p, Tiles tile);
};

#endif
