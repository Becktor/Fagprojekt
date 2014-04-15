/*
 *  The main sketch file, the root of all evil.
 *  Instead of using a separate file for the main game logic, updates and lists,
 *  use this.
 */

//Extern libraries
#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>

//Intern libraries
#include "Tiles.h"
#include "Scene.h"
#include "SceneGenerator.h"

//Constants
#define SECOND 1000 //Milis. in a second
#define INIT_FPS 60 //Initial assumed framerate.

//Global variables
static unsigned int _dTime = SECOND / INIT_FPS; //Approx. time between frames
static Scene _scene = Scene();

//Function declarations
void setup();
void loop();
void drawRect(int x, int y, int width, int height);
void drawTile(Tiles tile);

void setup() {
  randomSeed(analogRead(0)); //Initializes a random seed to the random generator (if pin 0 is unconnected)
  GD.begin();
  newScene(&_scene);
}

void loop() {
  unsigned long startMilis = millis();
  unsigned int fps = 0;
  while(millis() - startMilis < SECOND) { //Loop for a second
    //Game logic

    //Draw Logic
    GD.Clear();
    GD.ColorRGB(140, 140, 140);
    for(int i = 0; i < _scene.getWidth(); i++)
      for(int j = 0; j < _scene.getHeight(); j++)
        drawTile(i, j, _scene.getTile(i, j));
    GD.ColorRGB(255, 0, 0);
    GD.cmd_number(240,136, 31, OPT_CENTER, fps); 
    GD.swap();

    //Frame counter
    fps++;
  }
  _dTime = SECOND / fps;
}

void drawRect(int x, int y, int width, int height) {
  GD.Begin(RECTS);
  GD.Vertex2ii(x, y);
  GD.Vertex2ii(x + width - 2, y + height - 2);
}

void drawTile(int x, int y, Tiles tile) {
  if(tile != N)
    drawRect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
}
