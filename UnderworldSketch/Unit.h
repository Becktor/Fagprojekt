/*
 *  Currently non-abstract class of any one unit. Cannot be superclass
 *  to 'Entities' since entities uses points for positions while units use
 *  hitboxes. Could be superclass to future prop though.
 */

#ifndef unit_h
#define unit_h

#include "Direction.h"
#include "Logic.h"
#include "Prop.h"

class Logic;
class Unit : public Prop {
  public:
    byte _imageWidth;
    char _dir, _health, _handle, _cells;

    Unit(byte width, byte height, char health, byte imageWidth);
    void hit(byte damage, char force);
    boolean isDead();
    virtual void fillHealth();
    void toggleDir();
    virtual void updateAI(int dTime, Logic *logic);
    void xCollide();
    void yCollide();
};
#endif
