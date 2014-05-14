#ifndef prop_h
#define prop_h

#include "Direction.h"
#include "Geo.h"

class Prop
{
  private:
    Rect _hitbox;

  public:
    Prop(int x, int y, int width, int height);
    //Prop(Rect *hitbox);
    Rect* getHitbox();
    void translate(int x,int y);
};
#endif
