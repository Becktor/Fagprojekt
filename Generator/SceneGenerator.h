#ifndef sceneGen_h
#define sceneGen_h

#include <Arduino.h>
#include "Tiles.h"
#include "Geo.h"
#include "Scene.h"

void newScene(Scene *scene);
void generate(Scene *scene, Modules modules[XMODULES][YMODULES], Point *entrance, Point *exit);
void getRandModule(Modules module, Tiles (**tiles)[MODULE_WIDTH][MODULE_HEIGHT]);
void fillModule(Scene *scene, Modules module, int dX, int dY);
void modulate(Modules modules[XMODULES][YMODULES], Point *entrance, Point *exit);
void shell(Scene *scene);
#endif
