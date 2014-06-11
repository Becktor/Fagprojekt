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
  private:

  public:
    byte _imageWidth, _health, _handle, _cells, _currentCell;
    char _dir;
    long _FR, _millis;
    
    Unit(byte width, byte height, char health, byte imageWidth);
    void hit(byte damage, char force);
    virtual void fillHealth();
    void checkFrameChange(long milis);
    void toggleDir();
    void updateHandle(byte handle, byte cell);
    virtual void updateAI(int dTime, Logic *logic);
    void xCollide();
    void yCollide();
};
#endif
