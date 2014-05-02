#ifndef sceneGen_h
#define sceneGen_h

#include <Arduino.h>
#include "Tiles.h"
#include "Geo.h"
#include "Scene.h"

void clearScene(Scene *scene);
void fillModule(Scene *scene, Modules module, int dX, int dY, boolean isPortalRoom, boolean isEntrance, Point *portal);
void generate(Scene *scene, Modules modules[XMODULES][YMODULES], Point *entrance, Point *exit);
void modulate(Modules modules[XMODULES][YMODULES], Point *entrance, Point *exit);
void newScene(Scene *scene, Point *entrance, Point *exit);
void shell(Scene *scene);
#endif
