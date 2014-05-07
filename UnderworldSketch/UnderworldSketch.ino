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
#define NUNCHUCK 0 //Whether or not a nunchuck is connected

//Constants
const static short
    SCREEN_WIDTH = 480,
    SCREEN_HEIGHT = 272,
    SCREEN_TILES_WIDTH = SCREEN_WIDTH / TILE_SIZE,
    SCREEN_TILES_HEIGHT = SCREEN_HEIGHT / TILE_SIZE,
    SECOND = 1000, //Milis. in a second
    INIT_FPS = 60; //Initial assumed framerate.

//Global variables
static int _cameraX = 0, _cameraY = 0;
static unsigned int _dTime = SECOND / INIT_FPS; //Approx. time between frames
static Scene _scene = Scene();
static Logic _logic = Logic(&_scene);
static Point _entrance = Point(), _exit = Point();
static ArduinoNunchuk _nunchuk = ArduinoNunchuk();

//Temporary units
static Minotaur _mino(48, 70);
static Hero _hero(140,70, &_nunchuk);

//Function declarations
void setup();
void loop();
void drawRect(int x, int y, int width, int height);
void drawTile(Tiles tile);
void drawUnit(Unit *unit);

void setup() {
  randomSeed(107); //Initializes a random seed to the random generator (if pin 0 is unconnected)
  if(NUNCHUCK)
    _nunchuk.init();
  GD.begin();
  newScene(&_scene, &_entrance, &_exit);
  _logic.setHero(&_hero);
  _scene.addUnit(&_mino, new Point(1, 1));
  _scene.addUnit(&_hero, &_entrance);
}

void loop() {
  unsigned long startMilis = millis();
  short fps = INIT_FPS, counter = 0;
  while(millis() - startMilis < SECOND) { //Loop for a second
    LinkedList<Unit*>* units = _scene.getUnits();
    //Game logic
    if(NUNCHUCK) {
      _nunchuk.update();
      _nunchuk.update();
    }
    for(int i = 0; i < units->size(); i++) {
      Unit *unit = units->get(i);
      unit->updateAI(_dTime, &_logic);
      unit->updatePhysics(_dTime, &_logic);
    }
    //Game end
    if(_logic.isGameOver()) {
      if(_logic.isHeroWin()) {
        //Game continue
      } else {
        //Game restart
      }
      newScene(&_scene, &_entrance, &_exit);
      _scene.clearUnits();
      _logic.restartGame();
      _scene.addUnit(&_mino, new Point(1, 1));
      _scene.addUnit(&_hero, &_entrance);
    }
    //Draw Logic
    GD.Clear();
    GD.Begin(RECTS);
    Rect* hitbox = _mino.getHitbox();
    _cameraX = hitbox->getX() + (hitbox->getWidth() - SCREEN_WIDTH) / 2;
    _cameraY = hitbox->getY() + (hitbox->getHeight() - SCREEN_HEIGHT) / 2;
    drawScene();
    GD.ColorRGB(255, 0, 0);
    for(int i = 0; i < units->size(); i++)
      drawUnit(units->get(i));
    //GD.cmd_number(40,136, 31, OPT_CENTER, fps); 
    GD.swap();
    //Frame counter
    counter++;
  }
  fps = counter;
  _dTime = SECOND / fps;
}

void drawRect(int x, int y, int width, int height) {
  int rectX1 = x - _cameraX, rectY1 = y - _cameraY, rectX2 = x + width - 2 - _cameraX, rectY2 = y + height - 2 - _cameraY;
  if(rectX1 >= 0 && rectX2 < SCREEN_WIDTH && rectY1 >= 0 && rectY2 < SCREEN_HEIGHT) {
    GD.Vertex2ii(rectX1, rectY1);
    GD.Vertex2ii(rectX2, rectY2);
  }
}

void drawScene() {
  GD.ColorRGB(140, 140, 140);
  int tileX = _cameraX / TILE_SIZE,
      tileY = _cameraY / TILE_SIZE,
      tileXEnd = (_cameraX + SCREEN_WIDTH - 1) / TILE_SIZE,
      tileYEnd = (_cameraY + SCREEN_HEIGHT - 1) / TILE_SIZE;
  if(_cameraX < 0)
    tileX--;
  if(_cameraY < 0)
    tileY--;
  if(_cameraX + SCREEN_WIDTH - 1 < 0)
    tileXEnd--;
  if(_cameraY + SCREEN_HEIGHT - 1 < 0)
    tileYEnd--;
  for(int i = tileX; i < tileXEnd; i++) {
    for(int j = tileY; j < tileYEnd; j++) {
      drawTile(i, j, _scene.getTile(i, j));
    }
  }
}

void drawTile(int x, int y, Tiles tile) {
  if(tile != NONE)
    drawRect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
}

void drawUnit(Unit* unit) {
  Rect *hitbox = unit->getHitbox();
//  drawRect(hitbox->getX(), hitbox->getY(), hitbox->getWidth(), hitbox->getHeight());
GD.Begin(BITMAPS);
GD.Vertex2ii(hitbox->getX(), hitbox->getY(), SPRITE0_HANDLE, (hitbox->getX() >> 2) & 5);
}
