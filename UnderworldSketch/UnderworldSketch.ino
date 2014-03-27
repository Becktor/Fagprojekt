/*
 *  The main sketch file, the root of all evil.
 *  Instead of using a separate file for the main game logic, updates and lists,
 *  use this.
 */

#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>

#include "Geo.h"
#include "Scene.h"
#include "Unit.h"
#include "Logic.h"

#define SECOND 1000 //Milis. in a second
#define INIT_FPS 60 //Initial assumed framerate.

static unsigned int _dTime = SECOND / INIT_FPS; //Approx. time between frames
static Scene _scene = Scene();
static Logic _logic = Logic(&_scene);
static Unit _unit(1, Rect( Point(2, 2), 1, 1));

void shellScene();
void setup();
void loop();

void setup() {
  GD.begin();
}

void loop() {
  unsigned long startMilis = millis();
  unsigned int fps = 0;
  while(millis() - startMilis < SECOND) { //Loop for a second
    //Game update
    fps++;
  }
  _dTime = SECOND / fps;
}

//Should be in a separate scene generation library.
/*
void shellScene() {
 for(int i = 0; i < SCENE_WIDTH; i++) {
 _scene.setTile(i, 0, Rock);
 _scene.setTile(i, SCENE_HEIGHT - 1, Rock);
 }
 for(int i = 1; i < SCENE_HEIGHT - 1; i++) {
 _scene.setTile(0, i, Rock);
 _scene.setTile(SCENE_WIDTH - 1, i, Rock);
 }
 }
 */

