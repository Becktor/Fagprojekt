/*
 *  The unit class. Contains virtual AI function to be overwritten by superclasses.
 */

#ifndef unit_h
#define unit_h

#include "Direction.h"
#include "Logic.h"
#include "Prop.h"

class Logic;
class Unit : public Prop {
  public:
    boolean _isScored; //Whether the hero has recieved points for this unit.
    byte _health, _score;
    
    Unit(byte width, byte height, byte health, byte score, byte imageWidth, byte imageHeight, word invTime);
    void collideX();
    void collideY();
    virtual void hit(byte damage, char force);
    virtual void initialize();
    void toggleDir();
    virtual void updateAI(byte dTime, Logic *logic);
};
#endif
