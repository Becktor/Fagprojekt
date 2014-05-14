#ifndef sceneGen_h
#define sceneGen_h

#include <Arduino.h>
#include "Geo.h"
#include "Scene.h"

void clearScene(Scene *scene);
void fillModule(Scene *scene, byte module, byte dX, byte dY, boolean isPortalRoom, boolean isEntrance, Point *portal);
void generate(Scene *scene, byte modules[XMODULES][YMODULES], Point *entrance, Point *exit);
void modulate(byte modules[XMODULES][YMODULES], Point *entrance, Point *exit);
void newScene(Scene *scene, Point *entrance, Point *exit);
void shell(Scene *scene);
#endif
