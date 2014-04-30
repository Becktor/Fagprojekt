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
#include "Tiles.h"
#include "Scene.h"
#include "SceneGenerator.h"
#include "Logic.h"
#include "Unit.h"
#include "Minotaur.h"
#include "Hero.h"

//Checks
#define NUNCHUCK 1 //Whether or not a nunchuck is connected

//Constants
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272
#define SCREEN_TILES_WIDTH SCREEN_WIDTH / TILE_SIZE
#define SCREEN_TILES_HEIGHT SCREEN_HEIGHT / TILE_SIZE
#define SECOND 1000 //Milis. in a second
#define INIT_FPS 60 //Initial assumed framerate.

//Global variables
static int cameraX = 0, cameraY = 0;
static unsigned int _dTime = SECOND / INIT_FPS; //Approx. time between frames
static Scene _scene = Scene();
static Logic _logic = Logic(&_scene);
static LinkedList<Unit*> units;
static ArduinoNunchuk nunchuk = ArduinoNunchuk();

//Temporary units
static Minotaur _mino1(48, 70);
static Hero _archon(140,70, &nunchuk);

//Function declarations
void setup();
void loop();
void drawRect(int x, int y, int width, int height);
void drawTile(Tiles tile);
void drawUnit(Unit *unit);

void setup() {
  randomSeed(107); //Initializes a random seed to the random generator (if pin 0 is unconnected)
  newScene(&_scene);
  if(NUNCHUCK)
    nunchuk.init();
  GD.begin();
  units.add(&_mino1);
  units.add(&_archon);
  //units.add(&_mino2);
  //units.add(&_mino3);
}

void loop() {
  unsigned long startMilis = millis();
  short fps = INIT_FPS, counter = 0;
  while(millis() - startMilis < SECOND) { //Loop for a second
    //Game logic
    if(NUNCHUCK) {
      nunchuk.update();
      nunchuk.update();
    }
    for(int i = 0; i < units.size(); i++) {
      Unit *unit = units.get(i);
      unit->updateAI(_dTime, &_logic);
      unit->updatePhysics(_dTime, &_logic);
    }
    //Draw Logic
    GD.Clear();
    GD.Begin(RECTS);
    Rect* hitbox = _archon.getHitbox();
    cameraX = hitbox->getX() + (hitbox->getWidth() - SCREEN_WIDTH) / 2;
    cameraY = hitbox->getY() + (hitbox->getHeight() - SCREEN_HEIGHT) / 2;
    drawScene();
    GD.ColorRGB(255, 0, 0);
    for(int i = 0; i < units.size(); i++)
      drawUnit(units.get(i));
    //GD.cmd_number(240,136, 31, OPT_CENTER, fps); 
    GD.swap();
    //Frame counter
    counter++;
  }
  fps = counter;
  _dTime = SECOND / fps;
}

void drawRect(int x, int y, int width, int height) {
  int rectX1 = x - cameraX, rectY1 = y - cameraY, rectX2 = x + width - 2 - cameraX, rectY2 = y + height - 2 - cameraY;
  if(rectX1 >= 0 && rectX2 < SCREEN_WIDTH && rectY1 >= 0 && rectY2 < SCREEN_HEIGHT) {
    GD.Vertex2ii(rectX1, rectY1);
    GD.Vertex2ii(rectX2, rectY2);
  }
}

void drawScene() {
  GD.ColorRGB(140, 140, 140);
  int tileX = cameraX / TILE_SIZE,
      tileY = cameraY / TILE_SIZE,
      tileXEnd = (cameraX + SCREEN_WIDTH - 1) / TILE_SIZE,
      tileYEnd = (cameraY + SCREEN_HEIGHT - 1) / TILE_SIZE;
  if(cameraX < 0)
    tileX--;
  if(cameraY < 0)
    tileY--;
  if(cameraX + SCREEN_WIDTH - 1 < 0)
    tileXEnd--;
  if(cameraY + SCREEN_HEIGHT - 1 < 0)
    tileYEnd--;
  for(int i = tileX; i < tileXEnd; i++) {
    for(int j = tileY; j < tileYEnd; j++) {
      drawTile(i, j, _scene.getTile(i, j));
    }
  }
}

void drawTile(int x, int y, Tiles tile) {
  if(tile != N)
    drawRect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
}

void drawUnit(Unit* unit) {
  Rect *hitbox = unit->getHitbox();
  drawRect(hitbox->getX(), hitbox->getY(), hitbox->getWidth(), hitbox->getHeight());
}
