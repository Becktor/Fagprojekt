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
#define RESET_HSCORE 1 //Resets highscore

//Constants
const static int
    ADDRESS_HSCORE = 100,
    ADDRESS_SEED = 102,
    INIT_FPS = 40, //Initial assumed framerate.
    SCREEN_WIDTH = 480,
    SCREEN_HEIGHT = 272,
    SCREEN_TILES_WIDTH = SCREEN_WIDTH / TILE_SIZE,
    SCREEN_TILES_HEIGHT = SCREEN_HEIGHT / TILE_SIZE,
    SECOND = 1000;

//Function declarations
void setup();
void loop();
void drawScene(Scene *scene, int offsetX, int offsetY);
void drawProp(Prop *prop, int offsetX, int offsetY);
void drawVertex2f(int x, int y, int offsetX, int offsetY);
void EEPROMWriteInt(int p_address, int p_value);
word EEPROMReadInt(int p_address);
void flip(byte halfWidth);

void setup() {
  //SETUP
  //Serial.begin(9600);
  word _score = 0, _highScore;
  if(RESET_HSCORE)
    _highScore = 0;
  else
    _highScore = EEPROMReadInt(ADDRESS_HSCORE);
  Scene _scene = Scene();
  Logic _logic = Logic(&_scene);
  ArduinoNunchuk _nunchuk = ArduinoNunchuk();
  Hero _hero(&_nunchuk);
  Rect *_camera = &(_hero._hitbox);
  word seed = EEPROMReadInt(ADDRESS_SEED);
  randomSeed(seed);
  EEPROMWriteInt(ADDRESS_SEED, random(65535)); //New random seed in unsigned int range.
  if(NUNCHUCK)
    _nunchuk.init();
  GD.begin();
  LOAD_ASSETS();
  Point _entrance = Point(), _exit = Point();
  newScene(&_scene, &_entrance, &_exit);
  _logic._hero = &_hero;
  _scene.addUnit(&_hero, _entrance._x, _entrance._y);

  LinkedList<Unit*>* units = _scene.getUnits();
  LinkedList<Coin*>* coins = _scene.getCoins();
  long currentMillis = millis();
  //LOOP
  for(;;) {
    //Time calculations
    long newMillis = millis();
    byte _dTime = newMillis - currentMillis;
    currentMillis = newMillis;
    //GAME LOGIC
    if(NUNCHUCK) {
      _nunchuk.update();
      _nunchuk.update();
    }
    //UPDATE AI
    for(byte i = 0; i < units->size(); i++) {
      Unit *unit = units->get(i);
      unit->updateAnimation(_dTime);
      unit->updateAI(_dTime, &_logic);
    }
    //UPDATE PROPS
    {
      byte i = 0;
      while(i < coins->size()) {
        Coin* coin = coins->get(i);
        coin->updateAnimation(_dTime);
        _logic.executeAttacks(coin);
        if(_logic.coinCollision(coin)){ {
          _score += COIN_SCORE;
          coins->remove(i);}
        } else {
          _logic.updatePhysics(_dTime, coin);
          i++;
        }
      }
    }
    {
      byte i = 0;
      while(i < units->size()) {
        Unit* unit = units->get(i);
        _logic.executeAttacks(unit);
        if(unit->_health == 0) {
          units->remove(i);
          _score += 100;
        } else {
          _logic.updatePhysics(_dTime, unit);
          i++;
        }
      }
    }
    _logic.clearAttacks();
    if(_hero.getAttackSound())
       GD.sample(ATTACK, ATTACK_LENGTH, 8000, ADPCM_SAMPLES);
    //Game end
    if(_hero._health == 0) {
      _logic._gameOver = true;
      _logic._heroWin = false;
    }
    if(_logic._gameOver) {
      byte health;
      if(_logic._heroWin) {
        //GAME CONTINUE
        health = _hero._health;
        GD.sample(EXIT, EXIT_LENGTH, 8000, ADPCM_SAMPLES);
      } else {
        //GAME RESTART
        health = HERO_HEALTH;
      }
      newScene(&_scene, &_entrance, &_exit);
      //MOVE TO GAME RESTART LATER
      if (_highScore < _score) {
        EEPROMWriteInt(ADDRESS_HSCORE, _score);
        _highScore = _score;
      }
      //
      _logic._gameOver = false;
      _logic._heroWin = false;
      _scene.addUnit(&_hero, _entrance._x, _entrance._y);
      _hero._health = health;
    }

    //DRAW LOGIC
    GD.ClearColorRGB(38, 36, 57); //Background
    GD.Clear();
    GD.Begin(BITMAPS);
    GD.ColorRGB(255,255,255);
    int cameraX = _camera->_x + (_camera->_width - SCREEN_WIDTH) / 2,
        cameraY = _camera->_y + (_camera->_height - SCREEN_HEIGHT) / 2;
    //Draw scene
    drawScene(&_scene, cameraX, cameraY);
    //Draw objects
    for(byte i = 0; i < coins->size(); i++)
      drawProp(coins->get(i), cameraX, cameraY);
    for(byte i = 0; i < units->size(); i++)
      drawProp(units->get(i), cameraX, cameraY);
    //Draw score
    GD.ColorRGB(255,255,255); //Text color
    GD.cmd_number(40, 40, 20, OPT_CENTER, _score);
    GD.cmd_number(60, 60, 20, OPT_CENTER, _highScore); 
    //Complete drawing
    GD.swap();
  }
}

void loop() { }

void drawScene(Scene *scene, int offsetX, int offsetY) {
  char tileXEnd = worldToGrid(offsetX + SCREEN_WIDTH - 1),
       tileYEnd = worldToGrid(offsetY + SCREEN_HEIGHT - 1);
  for(char tileX = worldToGrid(offsetX); tileX <= tileXEnd; tileX++) {
    for(char tileY = worldToGrid(offsetY); tileY <= tileYEnd; tileY++) {
      byte tile = scene->getTile(tileX, tileY);
      if(tile != NONE) {
        GD.BitmapHandle(TILE_HANDLE);        
        if(tile == ROCK)
          GD.Cell(0);
        else if(tile == PLATFORM)
          GD.Cell(1);
        else if(tile == START)
          GD.Cell(2);
        else if(tile == END)
          GD.Cell(2);
        drawVertex2f(gridToWorld(tileX) - offsetX, gridToWorld(tileY) - offsetY);
      }
    }
  }
}

void drawProp(Prop* prop,  int offsetX, int offsetY) {
  Rect *hitbox = &(prop->_hitbox);
  /* DRAW HITBOX
  GD.Begin(RECTS);
  GD.ColorRGB(200, 5, 200);
  if(hitbox->_x - offsetX > 0 && hitbox->_x - offsetX < SCREEN_WIDTH && hitbox->_y - offsetY > 0 && hitbox->_y - offsetY < SCREEN_HEIGHT){
    GD.Vertex2ii(hitbox->_x - offsetX, hitbox->_y - offsetY);
    GD.Vertex2ii(hitbox->_x + hitbox->_width - offsetX, hitbox->_y + hitbox->_height - offsetY);
  }
  GD.ColorRGB(255, 255, 255);
  */
  byte halfWidth = prop->_imageWidth / 2;
  if(prop->_dir == LEFT)
    flip(halfWidth);
  GD.BitmapHandle(prop->_handle);
  GD.Cell(prop->_currentCell);
  drawVertex2f(hitbox->_x - offsetX - (prop->_imageWidth - hitbox->_width) / 2, hitbox->_y - offsetY);
  if(prop->_dir == LEFT)
    flip(halfWidth);
}

void flip(byte halfWidth) {
  GD.cmd_translate(F16(halfWidth), F16(0));
  GD.cmd_scale(F16(-1), F16(1));
  GD.cmd_translate(F16(-halfWidth), F16(0));
  GD.cmd_setmatrix();
}

void drawVertex2f(int x, int y) {
  GD.Vertex2f(x* 16, y * 16);
}

void EEPROMWriteInt(int p_address, int p_value) {
  byte lowByte = ((p_value >> 0) & 0xFF),
      highByte = ((p_value >> 8) & 0xFF);
  EEPROM.write(p_address, lowByte);
  EEPROM.write(p_address + 1, highByte);
}

word EEPROMReadInt(int p_address) {
  byte lowByte = EEPROM.read(p_address),
      highByte = EEPROM.read(p_address + 1);
  return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
}
