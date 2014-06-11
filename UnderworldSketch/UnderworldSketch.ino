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
    ADDRESS_Hscore =200,
    SCREEN_TILES_WIDTH = SCREEN_WIDTH / TILE_SIZE,
    SCREEN_TILES_HEIGHT = SCREEN_HEIGHT / TILE_SIZE,
    SECOND = 1000,
    INIT_FPS = 40; //Initial assumed framerate.

//Function declarations
void setup();
void loop();
void drawScene(Scene *scene, int offsetX, int offsetY);
void drawProp(Prop *prop, int offsetX, int offsetY, long currentMilis);
void drawVertex2f(int x, int y, int offsetX, int offsetY);

void setup() {
  //INIT
  Serial.begin(9600);
  byte _fps = INIT_FPS;
  word _dTime = SECOND / INIT_FPS; //Approx. time between frames

  Scene _scene = Scene();
  Logic _logic = Logic(&_scene);
  unsigned int CURRENT_Hscore = EEPROMReadInt(ADDRESS_Hscore);
  ArduinoNunchuk _nunchuk = ArduinoNunchuk();
  Hero _hero(&_nunchuk);
  Rect *_camera = &(_hero._hitbox);

  //SETUP
  randomSeed(5); //Initializes a random seed to the random generator
  if(NUNCHUCK)
    _nunchuk.init();
  GD.begin();
  LOAD_ASSETS();
  //  GD.BitmapHandle(0);
  //  GD.cmd_loadimage(0, 0);
  //  GD.load("healsky.jpg");
  Point _entrance = Point(), _exit = Point();
  newScene(&_scene, &_entrance, &_exit);
  _logic.setHero(&_hero);
  _scene.addUnit(&_hero, _entrance._x, _entrance._y);

  LinkedList<Unit*>* units = _scene.getUnits();
  LinkedList<Prop*>* props = _scene.getProps();
  //LOOP
  for(;;) {
    //FPS CALCULATIONS
    byte _counter = 0;
    unsigned long startMillis = millis(), currentMillis = startMillis;
    while(currentMillis - startMillis < SECOND) { //Loop for a second
      //GAME LOGIC
      if(NUNCHUCK) {
        _nunchuk.update();
        _nunchuk.update();
      }
      //UPDATE AI
      for(byte i = 0; i < units->size(); i++)
        units->get(i)->updateAI(_dTime, &_logic);
      //UPDATE PROPS
      {
        byte i = 0;
        while(i < props->size()) {
          Prop* prop = props->get(i);
          _logic.executeAttacks(prop);
          if(_logic.coinCol(prop)){
            props->remove(i);}
          else {
            _logic.updatePhysics(prop, _dTime);
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
            _logic._score += 100;
          } else {
            _logic.updatePhysics(unit, _dTime);
            i++;
          }
        }
      }
      _logic.clearAttacks();
      if (_hero.getAttackSound())
         GD.sample(ATTACK, ATTACK_LENGTH, 8000, ADPCM_SAMPLES);
      //Game end
      if(_hero._health == 0)
          _logic._gameOver = true;
          _logic._heroWin = false;

      if(_logic._gameOver) {
        if(_logic._heroWin) {
          //GAME CONTINUE
          GD.sample(EXIT, EXIT_LENGTH, 8000, ADPCM_SAMPLES);
        } else {
          //GAME RESTART
        }
        newScene(&_scene, &_entrance, &_exit);
        if (CURRENT_Hscore < _logic._score){
         EEPROMWriteInt(ADDRESS_Hscore, _logic._score);
         CURRENT_Hscore = EEPROM.read(ADDRESS_Hscore);
         Serial.println(CURRENT_Hscore);
       }
        _logic._gameOver = false;
        _logic._heroWin = false;
        _scene.addUnit(&_hero, _entrance._x, _entrance._y);
      }

      //DRAW LOGIC
      GD.ClearColorRGB(255,255,255); //Background
      GD.Clear();
      GD.Begin(BITMAPS);
      int cameraX = _camera->_x + (_camera->_width - SCREEN_WIDTH) / 2,
          cameraY = _camera->_y + (_camera->_height - SCREEN_HEIGHT) / 2;
      //Draw scene
      drawScene(&_scene, cameraX, cameraY);
      GD.ColorRGB(255, 0, 0); //Obsolete
      //Draw objects
      for(byte i = 0; i < units->size(); i++)
        drawProp(units->get(i), cameraX, cameraY, currentMillis);
      for(byte i = 0; i < props->size(); i++)
        drawProp(props->get(i), cameraX, cameraY, currentMillis);
      //Draw score
      GD.ColorRGB(0,0,0);
      GD.cmd_number(40, 40, 20, OPT_CENTER, _logic._score);
      //GD.cmd_text(40, 60, 20, OPT_CENTER,"Current Highscore");
      GD.cmd_number(60, 60, 20, OPT_CENTER, CURRENT_Hscore); 
      //Draw currentmilis/fps - temporary
      //GD.cmd_number(80, 136, 31, OPT_CENTER, currentMillis);
      GD.ColorRGB(255,255,255);
      //Complete drawing
      GD.swap();
      //Time calculations
      _counter++; //Frame counter
      currentMillis = millis();
      _fps = _counter;
      _dTime = SECOND / _fps;
    }
  }
}

void loop() { }

void drawScene(Scene *scene, int offsetX, int offsetY) {
  GD.ColorRGB(255, 255, 255); //Slated for removal
  char tileXEnd = worldToGrid(offsetX + SCREEN_WIDTH - 1),
       tileYEnd = worldToGrid(offsetY + SCREEN_HEIGHT - 1);
  for(char tileX = worldToGrid(offsetX); tileX <= tileXEnd; tileX++) {
    for(char tileY = worldToGrid(offsetY); tileY <= tileYEnd; tileY++) {
      byte tile = scene->getTile(tileX, tileY);
      if(tile != NONE) {
        int x = tileX, y = tileY;
        GD.BitmapHandle(TILE_HANDLE);
        drawVertex2f(gridToWorld(x) - offsetX, gridToWorld(y) - offsetY);
      }
    }
  }
}

void drawProp(Prop* prop,  int offsetX, int offsetY, long currentMilis) {
  Rect *hitbox = &(prop->_hitbox);
  GD.Begin(RECTS);
  GD.ColorRGB(200, 5, 200);
  if(hitbox->_x - offsetX > 0 && hitbox->_x - offsetX < SCREEN_WIDTH && hitbox->_y - offsetY > 0 && hitbox->_y - offsetY < SCREEN_HEIGHT){
    GD.Vertex2ii(hitbox->_x - offsetX, hitbox->_y - offsetY);
    GD.Vertex2ii(hitbox->_x + hitbox->_width - offsetX, hitbox->_y + hitbox->_height - offsetY);
  }
  GD.Begin(BITMAPS);

  //drawRect(hitbox->getX(), hitbox->getY(), hitbox->getWidth(), hitbox->getHeight());
  GD.ColorRGB(255, 255, 255);
  int half_Width = prop->_imageWidth / 2;
  int xfix = (prop->_imageWidth - hitbox->_width) / 2;
  prop->checkFrameChange(currentMilis);
  GD.BitmapHandle(prop->_handle);
  if(prop->_dir == LEFT) {
    xfix = -xfix + prop->_imageWidth - hitbox->_width;
    GD.cmd_translate(F16(half_Width), F16(0));
    GD.cmd_scale(F16(-1), F16(1));
    GD.cmd_translate(F16(-half_Width), F16(0));
    GD.cmd_setmatrix();
  }
  GD.Cell(prop->_currentCell);
  drawVertex2f(hitbox->_x - offsetX - xfix, hitbox->_y - offsetY);
  if(prop->_dir == LEFT) {
    GD.cmd_translate(F16(half_Width), F16(0));
    GD.cmd_scale(F16(-1), F16(1));
    GD.cmd_translate(F16(-half_Width), F16(0));
    GD.cmd_setmatrix();
  }
}

void drawVertex2f(int x, int y) {
  GD.Vertex2f(x* 16, y * 16);
}
void EEPROMWriteInt(int p_address, int p_value)
      {
      byte lowByte = ((p_value >> 0) & 0xFF);
      byte highByte = ((p_value >> 8) & 0xFF);

      EEPROM.write(p_address, lowByte);
      EEPROM.write(p_address + 1, highByte);
      }
unsigned int EEPROMReadInt(int p_address)
      {
      byte lowByte = EEPROM.read(p_address);
      byte highByte = EEPROM.read(p_address + 1);

      return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
      }
