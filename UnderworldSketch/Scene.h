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

#define TILE_SIZE 48 //One tile unit to world units conv.
#define SCENE_WIDTH 5
#define SCENE_HEIGHT 5

class Scene
{
  Tiles _tiles[SCENE_WIDTH][SCENE_HEIGHT];
  public:
    Scene();
    boolean contains(int x, int y);
    int getWidth();
    int getHeight();
    Tiles getTile(int x, int y);
    void setTile(int x, int y, Tiles tile);
    boolean tileIsSolid(int x, int y);
};

#endif
