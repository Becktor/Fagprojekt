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
#include "Prop.h"
#include "Coin.h"
#include "Scene.h"
#include "Logic.h"
#include "Unit.h"
#include "Hero.h"
#include "SceneGenerator.h"
#include "Sprites.h"

//Checks
#define NUNCHUCK 1 //Whether or not a nunchuck is connected

//Constants
const static int
    SCREEN_WIDTH = 480,
    SCREEN_HEIGHT = 272,
    SCREEN_TILES_WIDTH = SCREEN_WIDTH / TILE_SIZE,
    SCREEN_TILES_HEIGHT = SCREEN_HEIGHT / TILE_SIZE,
    SECOND = 1000, //Milis. in a second
    INIT_FPS = 40; //Initial assumed framerate.

//Function declarations
void setup();
void loop();
void drawProp(Prop *prop, int offsetX, int offsetY);
void drawScene(Scene *scene, int offsetX, int offsetY);
void drawScore(byte x, byte y, int n);
void drawTile(int x, int y, byte tile, int offsetX, int offsetY);
void drawUnit(Unit *unit, int offsetX, int offsetY);

void setup() {
  //INIT
  word _dTime = SECOND / INIT_FPS, _fps = INIT_FPS; //Approx. time between frames
  Scene _scene = Scene();
  Logic _logic = Logic(&_scene);
  ArduinoNunchuk _nunchuk = ArduinoNunchuk();
  Hero _hero(&_nunchuk);

  //SETUP
  randomSeed(107); //Initializes a random seed to the random generator
  if(NUNCHUCK)
    _nunchuk.init();
  GD.begin();
  LOAD_ASSETS();
  //  GD.BitmapHandle(0);
  //  GD.cmd_loadimage(0, 0);
  //  GD.load("healsky.jpg");
  Point _entrance = Point(0, 0), _exit = Point(0, 0);
  newScene(&_scene, &_entrance, &_exit);
  _logic.setHero(&_hero);
  _scene.addUnit(&_hero, _entrance.getX(), _entrance.getY());

  Coin _coin = Coin();
  _scene.addProp(&_coin, _exit.getX(), _exit.getY());

  LinkedList<Unit*>* units = _scene.getUnits();
  LinkedList<Prop*>* props = _scene.getProps();
  //LOOP
  for(;;) {
    //FPS CALCULATIONS
    unsigned long startMillis = millis(), currentMillis = startMillis;
    byte counter = 0;
    while(currentMillis - startMillis < SECOND) { //Loop for a second

      //GAME LOGIC
      if(NUNCHUCK) {
        _nunchuk.update();
        _nunchuk.update();
      }
      //UPDATE AI
      for(int i = 0; i < units->size(); i++) {
        Unit *unit = units->get(i);
        if(unit->isDead()) {
          units->remove(i);
          i--;
          _hero._score = _hero._score + 100;
        } else
          unit->updateAI(_dTime, &_logic);
      } 
      //UPDATE ATTACKS
      for(int i = 0; i < props->size(); i++)
        _logic.executeAttacks(props->get(i));
      for(int i = 0; i < units->size(); i++)
        _logic.executeAttacks(units->get(i));
      _logic.clearAttacks();
      if (_hero.getAttackSound())
         GD.sample(ATTACK,ATTACK_LENGTH, 8000, ADPCM_SAMPLES);

      //UPDATE PHYSICS
      for(int i = 0; i < props->size(); i++)
        _logic.updatePhysics(props->get(i), _dTime);
      for(int i = 0; i < units->size(); i++)
        _logic.updatePhysics(units->get(i), _dTime);
      //Game end
      if(_hero.isDead())
        _logic.setGameOver(true, false);
      if(_logic.isGameOver()) {
        if(_logic.isHeroWin()) {
          //GAME CONTINUE
          GD.sample(EXIT,EXIT_LENGTH, 8000, ADPCM_SAMPLES);
        } else {
          //GAME RESTART
        }
        newScene(&_scene, &_entrance, &_exit);
        _logic.restartGame();
        _scene.addUnit(&_hero, _entrance.getX(), _entrance.getY());
      }

      //DRAW LOGIC
      GD.ClearColorRGB(255,255,255);
      GD.Clear();
      //GD.Begin(RECTS);
      GD.Begin(BITMAPS);
      //Rect *hitbox = _hero.getHitbox();
      Rect *hitbox = &(units->get(0)->_hitbox);
      int cameraX = hitbox->getX() + (hitbox->getWidth() - SCREEN_WIDTH) / 2,
          cameraY = hitbox->getY() + (hitbox->getHeight() - SCREEN_HEIGHT) / 2;
      drawScene(&_scene, cameraX, cameraY);
      GD.ColorRGB(255, 0, 0);
      for(int i = 0; i < units->size(); i++)
        drawUnit(units->get(i), cameraX, cameraY, currentMillis);
      for(int i = 0; i < props->size(); i++)
        drawProp(props->get(i), cameraX, cameraY);
      drawScore(10,10,_hero._score);
      GD.cmd_number(40, 136, 31, OPT_CENTER, currentMillis); 
      //GD.Begin(BITMAPS);
      //GD.Vertex2ii(x * TILE_SIZE, y * TILE_SIZE, 0);
      GD.swap();
      counter++; //Frame counter
      currentMillis = millis();
    }
    //FPS CALCULATION
    _fps = counter;
    _dTime = SECOND / _fps;
  }
}

void loop() { }

void drawScene(Scene *scene, int offsetX, int offsetY) {
  GD.ColorRGB(255, 255, 255);
  int tileX = offsetX / TILE_SIZE,
      tileY = offsetY / TILE_SIZE,
      tileXEnd = (offsetX + SCREEN_WIDTH - 1) / TILE_SIZE,
      tileYEnd = (offsetY + SCREEN_HEIGHT - 1) / TILE_SIZE;
  if(offsetX < 0)
    tileX--;
  if(offsetY < 0)
    tileY--;
  if(offsetX + SCREEN_WIDTH - 1  < 0)
    tileXEnd--;
  if(offsetY + SCREEN_HEIGHT - 1  < 0)
    tileYEnd--;
  for(int i = tileX; i <= tileXEnd; i++) {
    for(int j = tileY; j <= tileYEnd; j++) {
      drawTile(i, j, scene->getTile(i, j), offsetX, offsetY);
    }
  }
}

void drawTile(int x, int y, byte tile, int offsetX, int offsetY) {
  if(tile != NONE) {
    GD.BitmapHandle(TILE_HANDLE);
    GD.Vertex2f(((x * TILE_SIZE) - offsetX) * 16, ((y * TILE_SIZE) - offsetY) * 16);
  }
}

//void drawUnit(Unit* unit, int offsetX, int offsetY) {
//  Rect *hitbox = unit->getHitbox();
//  GD.ColorRGB(255, 255, 255);
//  if(unit->getDir() == LEFT) {
//    GD.cmd_translate(F16(21), F16(0));
//    GD.cmd_scale(F16(-1), F16(1));
//    GD.cmd_translate(F16(-21), F16(0));
//    GD.cmd_setmatrix();
//  }
//  GD.BitmapHandle(SONICW_HANDLE);
//  GD.Cell((hitbox->getX() >> 4) & 7);
//  GD.Vertex2f((hitbox->getX() - offsetX) * 16, (hitbox->getY() - offsetY) * 16);
//  if(unit->getDir() == LEFT) {
//    GD.cmd_translate(F16(21), F16(0));
//    GD.cmd_scale(F16(-1), F16(1));
//    GD.cmd_translate(F16(-21), F16(0));
//    GD.cmd_setmatrix();
//  }
  
//}

void drawUnit(Unit* unit,  int offsetX, int offsetY, long currentMillis) {
  Rect *hitbox = &(unit->_hitbox);
  //drawRect(hitbox->getX(), hitbox->getY(), hitbox->getWidth(), hitbox->getHeight());
  GD.ColorRGB(255, 255, 255);
  int half_Width = hitbox->getWidth() / 2;
  int changeSpeed = 2;
  if(unit->getCells() == 1)
    changeSpeed=2;
  GD.BitmapHandle(unit->getHandle());
  if(unit->getDir() == -1) {
    GD.cmd_translate(F16(half_Width), F16(0));
    GD.cmd_scale(F16(-1), F16(1));
    GD.cmd_translate(F16(-half_Width), F16(0));
    GD.cmd_setmatrix();
  }
    GD.Cell((currentMillis >> changeSpeed) & unit->getCells());
    
  GD.Vertex2f((hitbox->getX() - offsetX) * 16, (hitbox->getY() - offsetY) * 16);
  if(unit->getDir() == -1) {
    GD.cmd_translate(F16(half_Width), F16(0));
    GD.cmd_scale(F16(-1), F16(1));
    GD.cmd_translate(F16(-half_Width), F16(0));
    GD.cmd_setmatrix();
  }
}

void drawProp(Prop* prop, int offsetX, int offsetY){
  Rect *hitbox = &(prop->_hitbox);
  GD.Begin(BITMAPS);
  GD.ColorRGB(255, 255, 255);
  GD.PointSize(16*hitbox->getWidth());
  GD.Begin(POINTS);
  GD.ColorRGB(0xff8000); // orange
  GD.Vertex2ii(hitbox->getX() - offsetX, hitbox->getY()-offsetY);
}

void drawScore(byte x, byte y, int n) {
 GD.cmd_number(x, y, 31, OPT_CENTER, n); 
}
