/*
 *  The main sketch file, the root of all evil.
 *  Instead of using a separate file for the main game logic, updates and lists,
 *  use this.
 */

//Extern libraries
#include <ArduinoNunchuk.h>
#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>
#include <Wire.h>

//Intern libraries
#include "Geo.h"
#include "Scene.h"
#include "Unit.h"
#include "Logic.h"



//Constants
#define SECOND 1000 //Milis. in a second
#define INIT_FPS 60 //Initial assumed framerate.

//Global variables
static unsigned int _dTime = SECOND / INIT_FPS; //Approx. time between frames
static Scene _scene = Scene();
static Logic _logic = Logic(&_scene);
static Unit _unit(1, Rect( Point(2, 2), 1, 1));



//Function declarations
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
    _unit.update(_dTime, _logic);
    fps++;
    GD.ClearColorRGB(0x103000);
    GD.Clear();
    GD.cmd_text(240, 136, 31, OPT_CENTER, "Hello world");
    GD.swap();
  }

  _dTime = SECOND / fps;
}

