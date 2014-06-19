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
#define HITBOXES 0 //Draw hitboxes.
#define NUNCHUCK 1 //Nunchuck is connected.
#define RESET_HSCORE 1 //Reset highscore.

//Constants
const static int
    ADDRESS_HSCORE = 100, //The addresses use 2 spaces.
    ADDRESS_SEED = 102,
    INIT_DIFF = 3, //Initial difficulty, on a scale from 0 to MINOTAURS in scene.h.
    SCREEN_WIDTH = 480, //Pixel width and height of the screen.
    SCREEN_HEIGHT = 272,
    SCREEN_TILES_WIDTH = SCREEN_WIDTH / TILE_SIZE, //Tile width and height of the screen.
    SCREEN_TILES_HEIGHT = SCREEN_HEIGHT / TILE_SIZE;

//Function declarations
void setup();
void loop();
void drawProp(Prop *prop, int offsetX, int offsetY);
void drawScene(Scene *scene, int offsetX, int offsetY);
void drawVertex2f(int x, int y, int offsetX, int offsetY);
void EEPROMWriteInt(int p_address, int p_value);
word EEPROMReadInt(int p_address);
void flipImage(byte halfWidth);

void setup() {
  //SETUP
  word _score = 0, _highScore;
  byte difficulty = INIT_DIFF;
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
  newScene(&_scene, &_entrance, &_exit, difficulty);
  _logic._hero = &_hero;
  _scene.addUnit(&_hero, _entrance._x, _entrance._y);
  LinkedList<Unit*>* units = _scene.getUnits();
  LinkedList<Coin*>* coins = _scene.getCoins();

  //LOOP
  long currentMillis = millis();
  boolean drawInvulnerable = false; //Whether or not to draw invulnerable units. Is toggled every frame
  for(;;) {
    //Time calculations
    long newMillis = millis();
    byte _dTime = newMillis - currentMillis;
    currentMillis = newMillis;
    //GAME LOGIC
    if(NUNCHUCK)
      _nunchuk.update();
    drawInvulnerable = !drawInvulnerable; //Toggle drawInvulnerable
    //update units
    for(byte i = 0; i < units->size(); i++)
      units->get(i)->updateAI(_dTime, &_logic);
    //update coins
    {
      byte i = 0;
      while(i < coins->size()) {
        Coin* coin = coins->get(i);
        coin->updateAnimation(_dTime);
        coin->updateInvulnerability(_dTime);
        _logic.executeAttacks(coin);
        if(_logic.coinCollision(coin)){
          _score += COIN_SCORE;
          coins->remove(i);
          GD.sample(COIN, COIN_LENGTH, 32000, ADPCM_SAMPLES);
        } else {
          _logic.updatePhysics(_dTime, coin);
          i++;
        }
      }
    }
    //update units
    for(byte i = 0; i < units->size(); i++) {
      Unit* unit = units->get(i);
      unit->updateAnimation(_dTime);
      unit->updateInvulnerability(_dTime);
      _logic.executeAttacks(unit);
      _logic.updatePhysics(_dTime, unit);
      if(unit->_health == 0 && !unit->_isScored) {
        _score += unit->_score;
        unit->_isScored = true;
      }
    }
    _logic.clearAttacks();
    if(_hero.getAttackSound()) //Play attack sound
       GD.sample(ATTACK, ATTACK_LENGTH, 8000, ADPCM_SAMPLES);
    //Game resolution
    if(_hero._health == 0) {
      _logic._gameOver = true;
      _logic._heroWin = false;
    }
    if(_logic._gameOver) {
      byte health;
      if(_logic._heroWin) { //GAME CONTINUE
        health = _hero._health; //Hero keeps his health
        difficulty++;
        GD.sample(EXIT, EXIT_LENGTH, 8000, ADPCM_SAMPLES);
      } else { //GAME RESTART
        health = HERO_HEALTH; //Hero resets his health
        difficulty = INIT_DIFF;
        if (_highScore < _score) {
          EEPROMWriteInt(ADDRESS_HSCORE, _score);
          _highScore = _score;
        }
        _score = 0;
      }
      newScene(&_scene, &_entrance, &_exit, difficulty);
      _logic._gameOver = false;
      _logic._heroWin = false;
      _scene.addUnit(&_hero, _entrance._x, _entrance._y);
      _hero._health = health;
    }
    //DRAW LOGIC
    GD.ClearColorRGB(38, 36, 57); //Background
    GD.Clear();
    GD.Begin(BITMAPS);
    //GD.ColorRGB(255,255,255);
    int cameraX = _camera->_x + (_camera->_width - SCREEN_WIDTH) / 2,
        cameraY = _camera->_y + (_camera->_height - SCREEN_HEIGHT) / 2;
    //Draw scene
    drawScene(&_scene, cameraX, cameraY);
    //Draw Props
    for(byte i = 0; i < coins->size(); i++)
      drawProp(coins->get(i), cameraX, cameraY);
    for(byte i = 0; i < units->size(); i++) {
      Unit *unit = units->get(i);
      if(!drawInvulnerable || !unit->_invulnerable || unit->_health == 0) //Flash damaged units
        drawProp(unit, cameraX, cameraY);
    }
    //Draw hud
    //GD.ColorRGB(255,255,255); //Text color
    GD.cmd_text(60, 250, 29, OPT_CENTER, "Health");
    GD.cmd_number(60, 230, 29, OPT_CENTER, _hero._health);
    //GD.Begin(BITMAPS);
    //for(int i = 0; i < _hero._health; i++) {
    //  D.Vertex2ii(30 + (30), 240, HEART_HANDLE, 0);
    //}
    GD.cmd_text(300, 250, 29, OPT_CENTER, "Score");
    GD.cmd_number(300, 230, 29, OPT_CENTER, _score);
    GD.cmd_text(400, 250, 28, OPT_CENTER, "Highscore");
    GD.cmd_number(400, 230, 28, OPT_CENTER, _highScore);
    //Complete drawing
    GD.swap();
  }
}

void loop() { } //Unused

//Draws a prop, with the given camera offsets.
void drawProp(Prop* prop,  int offsetX, int offsetY) {
  Rect *hitbox = &(prop->_hitbox);
  if(HITBOXES) {
    GD.Begin(RECTS);
    GD.ColorRGB(200, 5, 200);
    if(hitbox->_x - offsetX > 0 && hitbox->_x - offsetX < SCREEN_WIDTH && hitbox->_y - offsetY > 0 && hitbox->_y - offsetY < SCREEN_HEIGHT){
      GD.Vertex2ii(hitbox->_x - offsetX, hitbox->_y - offsetY);
      GD.Vertex2ii(hitbox->_x + hitbox->_width - offsetX, hitbox->_y + hitbox->_height - offsetY);
    }
    GD.ColorRGB(255, 255, 255);
    GD.Begin(BITMAPS);
  }
  byte halfWidth = prop->_imageWidth / 2;
  if(prop->_dir == LEFT)
    flipImage(halfWidth);
  GD.BitmapHandle(prop->_handle);
  GD.Cell(prop->_currentCell);
  drawVertex2f(hitbox->_x - offsetX - (prop->_imageWidth - hitbox->_width) / 2, hitbox->_y - offsetY - (prop->_imageHeight - hitbox->_height) / 2);
  if(prop->_dir == LEFT)
    flipImage(halfWidth);
}

//Draws the scene with the given offsets.
void drawScene(Scene *scene, int offsetX, int offsetY) {
  char tileXEnd = worldToGrid(offsetX + SCREEN_WIDTH - 1),
       tileYEnd = worldToGrid(offsetY + SCREEN_HEIGHT - 1);
  for(char tileX = worldToGrid(offsetX); tileX <= tileXEnd; tileX++) {
    for(char tileY = worldToGrid(offsetY); tileY <= tileYEnd; tileY++) {
      byte tile = scene->getTile(tileX, tileY);
      if(tile != NONE) {
        GD.BitmapHandle(TILE_HANDLE);        
        if(tile == ROCK)
          GD.Cell(1);
        else if(tile == PLATFORM)
          GD.Cell(2);
        else if(tile == START)
          GD.Cell(4);
        else if(tile == END)
          GD.Cell(5);
        drawVertex2f(gridToWorld(tileX) - offsetX, gridToWorld(tileY) - offsetY);
      }
    }
  }
}

//Draws at pixels instead of 1/16 pixels (micropixels).
void drawVertex2f(int x, int y) {
  GD.Vertex2f(x* 16, y * 16);
}

//Writes an integer at the given p_address and p_address + 1.
void EEPROMWriteInt(int p_address, int p_value) {
  byte lowByte = ((p_value >> 0) & 0xFF),
      highByte = ((p_value >> 8) & 0xFF);
  EEPROM.write(p_address, lowByte);
  EEPROM.write(p_address + 1, highByte);
}

//Reads an integer stored at p_address and p_address + 1.
word EEPROMReadInt(int p_address) {
  byte lowByte = EEPROM.read(p_address),
      highByte = EEPROM.read(p_address + 1);
  return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
}

void flipImage(byte halfWidth) {
  GD.cmd_translate(F16(halfWidth), F16(0));
  GD.cmd_scale(F16(-1), F16(1));
  GD.cmd_translate(F16(-halfWidth), F16(0));
  GD.cmd_setmatrix();
}
