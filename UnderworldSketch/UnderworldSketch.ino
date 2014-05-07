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
#include "Prop.h"
#include "Coin.h"

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
static unsigned int _dTime = SECOND / INIT_FPS; //Approx. time between frames
static Scene _scene = Scene();
static Logic _logic = Logic(&_scene);
static Point _entrance = Point(), _exit = Point();
static ArduinoNunchuk _nunchuk = ArduinoNunchuk();

//Temporary units
static Minotaur _mino(48, 70);
static Hero _hero(140,70, &_nunchuk);
static Coin _coin(140,70);

//Function declarations
void setup();
void loop();
void drawRect(int x, int y, int width, int height);
void drawTile(Tiles tile);
void drawUnit(Unit *unit);
void drawProp(Prop *prop);

void setup() {
  randomSeed(107); //Initializes a random seed to the random generator (if pin 0 is unconnected)
  if(NUNCHUCK)
    _nunchuk.init();
  GD.begin();
  LOAD_ASSETS();
  newScene(&_scene, &_entrance, &_exit);
  _logic.setHero(&_hero);
  _scene.addUnit(&_mino, new Point(1, 1));
  _scene.addUnit(&_hero, &_entrance);
  _scene.addProp(&_coin, &_entrance);

}

void loop() {
  unsigned long startMilis = millis();
  short fps = INIT_FPS, counter = 0;
  while(millis() - startMilis < SECOND) { //Loop for a second
    LinkedList<Unit*>* units = _scene.getUnits();
    LinkedList<Prop*>* props = _scene.getProps();
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
      _scene.addProp(&_coin, &_entrance);
    }
    //Draw Logic
    GD.Clear();
    GD.Begin(RECTS);
    Rect* hitbox = _hero.getHitbox();
    _cameraX = hitbox->getX() + (hitbox->getWidth() - SCREEN_WIDTH) / 2;
    _cameraY = hitbox->getY() + (hitbox->getHeight() - SCREEN_HEIGHT) / 2;
    drawScene();
    GD.ColorRGB(255, 0, 0);
    for(int i = 0; i < units->size(); i++)
      drawUnit(units->get(i));
    //GD.cmd_number(40,136, 31, OPT_CENTER, fps);
    drawProp(props->get(0));
    GD.swap();
    //Frame counter
    counter++;
  }
  fps = counter;
  _dTime = SECOND / fps;
}

void drawRect(int x, int y, int width, int height) {
  int rectX1 = x - _cameraX, rectY1 = y - _cameraY, rectX2 = x + width - 2 - _cameraX, rectY2 = y + height - 2 - _cameraY;
//  if(rectX1 >= 0 && rectX2 < SCREEN_WIDTH && rectY1 >= 0 && rectY2 < SCREEN_HEIGHT) {
//    GD.Vertex2f(rectX1*16, rectY1*16);
//    GD.Vertex2f(rectX2*16, rectY2*16);
//  }
    GD.Vertex2f(rectX1*16, rectY1*16);
    GD.Vertex2ii(rectX2, rectY2);
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
GD.ColorRGB(255, 255, 255);
if(unit->getDir() == -1)
{
  GD.cmd_translate(F16(21), F16(0));
  GD.cmd_scale(F16(-1), F16(1));
  GD.cmd_translate(F16(-21), F16(0));
  GD.cmd_setmatrix();
}
GD.Vertex2ii(hitbox->getX() - _cameraX, hitbox->getY() - _cameraY, Sonic0_HANDLE, (hitbox->getX() >> 2) & 7);
if(unit->getDir() == -1)
{
  GD.cmd_translate(F16(21), F16(0));
  GD.cmd_scale(F16(-1), F16(1));
  GD.cmd_translate(F16(-21), F16(0));
  GD.cmd_setmatrix();
}

}
void drawProp(Prop* prop){
  Rect *hitbox = prop->getHitbox();
  GD.Begin(BITMAPS);
  GD.ColorRGB(255, 255, 255);
  GD.PointSize(16*hitbox->getWidth());
  GD.Begin(POINTS);
  GD.ColorRGB(0xff8000); // orange
  GD.Vertex2ii(hitbox->getX() - _cameraX, hitbox->getY()-_cameraY);
}
