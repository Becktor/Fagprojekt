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
#include "Sprites.h"

//Checks
#define NUNCHUCK 1 //Whether or not a nunchuck is connected


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
static unsigned int _dTime = SECOND / INIT_FPS, _fps = INIT_FPS; //Approx. time between frames
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
  LOAD_ASSETS();
  //  GD.BitmapHandle(0);
  //  GD.cmd_loadimage(0, 0);
  //  GD.load("healsky.jpg");
  newScene(&_scene, &_entrance, &_exit);
  _logic.setHero(&_hero);
  _scene.addUnit(&_mino, new Point(1, 1));
  _scene.addUnit(&_hero, &_entrance);
}

void loop() {
  unsigned long startMilis = millis();
  short counter = 0;
  while(millis() - startMilis < SECOND) { //Loop for a second
    LinkedList<Unit*>* units = _scene.getUnits();
    //Game logic
    if(NUNCHUCK) {
      _nunchuk.update();
      _nunchuk.update();
    }
    //AI
    for(int i = 0; i < units->size(); i++) {
      Unit *unit = units->get(i);
      if(unit->isDead()) {
        units->remove(i);
        i--;
      } 
      else {
        unit->updateAI(_dTime, &_logic);
      }
    }
    //Attacks
    _logic.executeAttacks();
    //Physics
    for(int i = 0; i < units->size(); i++) {
      Unit *unit = units->get(i);
      unit->updatePhysics(_dTime, &_logic);
    }
    //Game end
    if(_hero.isDead())
      _logic.setGameOver(true, false);
    if(_logic.isGameOver()) {
      if(_logic.isHeroWin()) {
        //Game continue
      } 
      else {
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
    //    GD.Begin(RECTS);
    GD.Begin(BITMAPS);

    Rect* hitbox = _hero.getHitbox();
    _cameraX = hitbox->getX() + (hitbox->getWidth() - SCREEN_WIDTH) / 2;
    _cameraY = hitbox->getY() + (hitbox->getHeight() - SCREEN_HEIGHT) / 2;
    drawScene();
    GD.ColorRGB(255, 0, 0);
    for(int i = 0; i < units->size(); i++)
      drawUnit(units->get(i));
    GD.cmd_number(40,136, 31, OPT_CENTER, _fps); 
    //GD.Begin(BITMAPS);
    //GD.Vertex2ii(x * TILE_SIZE, y * TILE_SIZE, 0);
    GD.swap();
    //Frame counter
    counter++;
  }
  _fps = counter;
  _dTime = SECOND / _fps;
}

void drawRect(int x, int y, int width, int height) {
  int rectX1 = x - _cameraX, rectY1 = y - _cameraY, rectX2 = x + width - 2 - _cameraX, rectY2 = y + height - 2 - _cameraY;
  //  if(rectX1 >= 0 && rectX2 < SCREEN_WIDTH && rectY1 >= 0 && rectY2 < SCREEN_HEIGHT) {
  //    GD.Vertex2f(rectX1*16, rectY1*16);
  //    GD.Vertex2f(rectX2*16, rectY2*16);
  //  }
  GD.Vertex2f(rectX1*16, rectY1*16);
  GD.Vertex2f(rectX2*16, rectY2*16);
}

void drawScene() {
  GD.ColorRGB(255, 255, 255);
  int tileX = _cameraX / TILE_SIZE,
  tileY = _cameraY / TILE_SIZE,
  tileXEnd = (_cameraX + SCREEN_WIDTH - 1) / TILE_SIZE,
  tileYEnd = (_cameraY + SCREEN_HEIGHT - 1) / TILE_SIZE;
  if(_cameraX < 0)
    tileX--;
  if(_cameraY < 0)
    tileY--;
  if(_cameraX + SCREEN_WIDTH - 1  < 0)
    tileXEnd--;
  if(_cameraY + SCREEN_HEIGHT - 1  < 0)
    tileYEnd--;
  for(int i = tileX; i <= tileXEnd; i++) {
    for(int j = tileY; j <= tileYEnd; j++) {
      drawTile(i, j, _scene.getTile(i, j));
    }
  }
}

void drawTile(int x, int y, Tiles tile) {
  if(tile != NONE){
    //    drawRect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
    GD.BitmapHandle(TILE_HANDLE);
    GD.Vertex2f(((x * TILE_SIZE) - _cameraX)*16, ((y * TILE_SIZE) - _cameraY)*16);
  }
}

void drawUnit(Unit* unit) {
  Rect *hitbox = unit->getHitbox();
  //  drawRect(hitbox->getX(), hitbox->getY(), hitbox->getWidth(), hitbox->getHeight());
  GD.ColorRGB(255, 255, 255);
  if(unit->getDir() == -1)
  {
    GD.cmd_translate(F16(21), F16(0));
    GD.cmd_scale(F16(-1), F16(1));
    GD.cmd_translate(F16(-21), F16(0));
    GD.cmd_setmatrix();
  }
  GD.BitmapHandle(SonicW_HANDLE);
  GD.Cell((hitbox->getX() >> 2) & 7);
  GD.Vertex2f((hitbox->getX() - _cameraX) * 16, (hitbox->getY() - _cameraY) * 16);
  if(unit->getDir() == -1)
  {
    GD.cmd_translate(F16(21), F16(0));
    GD.cmd_scale(F16(-1), F16(1));
    GD.cmd_translate(F16(-21), F16(0));
    GD.cmd_setmatrix();
  }
}

