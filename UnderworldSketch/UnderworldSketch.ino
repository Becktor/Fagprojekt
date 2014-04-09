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
#include <LinkedList.h>

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
static Unit _unit1(1, Rect( Point(2, 2), 1, 1));
static Unit _unit2(1, Rect( Point(3, 3), 1, 1));
static Unit _unit3(1, Rect( Point(6, 5), 1, 1));

LinkedList<Unit*> units;



//Function declarations
void shellScene();
void setup();
void loop();

void setup() {
  GD.begin();
  units.add(&_unit1);
  units.add(&_unit2);
  units.add(&_unit3);
}

void loop() {
  unsigned long startMilis = millis();
  unsigned int fps = 0;
  while(millis() - startMilis < SECOND) { //Loop for a second
    GD.Clear();
    GD.cmd_number(240, 136, 31, OPT_CENTER, fps);
    GD.swap();
//   _unit.update(_dTime, _logic);
    fps++;
  

    for(int i=0;i<units.size();i++){
      Unit *derp = units.get(i);
      derp->update(_dTime, _logic);
    }
    fps++;

  }
  _dTime = SECOND / fps;
}

