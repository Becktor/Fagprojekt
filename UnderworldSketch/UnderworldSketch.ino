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
#include "Minotaur.h"

//Constants
#define SECOND 1000 //Milis. in a second
#define INIT_FPS 60 //Initial assumed framerate.

//Global variables
static unsigned int _dTime = SECOND / INIT_FPS; //Approx. time between frames
static Scene _scene = Scene();
static Logic _logic = Logic(&_scene);

static LinkedList<Unit*> units;

//Temporary units
static Minotaur _mino1(2, 2);
static Minotaur _mino2(3, 3);
static Minotaur _mino3(6, 5);

//Function declarations
void setup();
void loop();

void setup() {
  GD.begin();
  units.add(&_mino1);
  units.add(&_mino2);
  units.add(&_mino3);
}

void loop() {
  unsigned long startMilis = millis();
  unsigned int fps = 0;
  while(millis() - startMilis < SECOND) { //Loop for a second
    //Game logic
    for(int i = 0; i < units.size(); i++){
      Unit *unit = units.get(i);
      unit->updateAI(_dTime, &_logic);
      unit->updatePhysics(_dTime, &_logic);
    }

    //Draw Logic
    GD.Clear();
    GD.cmd_number(240, 136, 31, OPT_CENTER, fps);
    GD.swap();

    //Frame counter
    fps++;
  }
  _dTime = SECOND / fps;
}
