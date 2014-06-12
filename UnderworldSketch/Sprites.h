#ifndef sprites_h
#define sprites_h

//#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>

#define LOAD_ASSETS()  GD.safeload("Sprites.GD2");
#define HERO_MOVING_HANDLE 0
#define HERO_MOVING_WIDTH 74
#define HERO_MOVING_HEIGHT 48
#define HERO_MOVING_CELLS 8
#define HERO_ATTACKING_HANDLE 1
#define HERO_ATTACKING_WIDTH 74
#define HERO_ATTACKING_HEIGHT 48
#define HERO_ATTACKING_CELLS 2
#define HERO_DUCKING_HANDLE 2
#define HERO_DUCKING_WIDTH 74
#define HERO_DUCKING_HEIGHT 36
#define HERO_DUCKING_CELLS 2
#define HERO_IDLE_HANDLE 3
#define HERO_IDLE_WIDTH 74
#define HERO_IDLE_HEIGHT 48
#define HERO_IDLE_CELLS 2
#define MINO_CHARGING_HANDLE 4
#define MINO_CHARGING_WIDTH 80
#define MINO_CHARGING_HEIGHT 43
#define MINO_CHARGING_CELLS 4
#define MINO_DYING_HANDLE 5
#define MINO_DYING_WIDTH 80
#define MINO_DYING_HEIGHT 43
#define MINO_DYING_CELLS 4
#define MINO_WALKING_HANDLE 6
#define MINO_WALKING_WIDTH 80
#define MINO_WALKING_HEIGHT 43
#define MINO_WALKING_CELLS 4
#define TILE_HANDLE 7
#define TILE_WIDTH 48
#define TILE_HEIGHT 48
#define TILE_CELLS 4
#define COIN_HANDLE 8
#define COIN_WIDTH 32
#define COIN_HEIGHT 32
#define COIN_CELLS 4
#define ATTACK 205088UL
#define ATTACK_LENGTH 1600
#define ATTACK_FREQ 8000
#define JUMP 206688UL
#define JUMP_LENGTH 944
#define JUMP_FREQ 8000
#define EXIT 207632UL
#define EXIT_LENGTH 4000
#define EXIT_FREQ 8000
#define COIN 211632UL
#define COIN_LENGTH 4072
#define COIN_FREQ 22050
#define ASSETS_END 215704UL
static const shape_t HERO_MOVING_SHAPE = {0, 74, 48, 0};
static const shape_t HERO_ATTACKING_SHAPE = {1, 74, 48, 0};
static const shape_t HERO_DUCKING_SHAPE = {2, 74, 36, 0};
static const shape_t HERO_IDLE_SHAPE = {3, 74, 48, 0};
static const shape_t MINO_CHARGING_SHAPE = {4, 80, 43, 0};
static const shape_t MINO_DYING_SHAPE = {5, 80, 43, 0};
static const shape_t MINO_WALKING_SHAPE = {6, 80, 43, 0};
static const shape_t TILE_SHAPE = {7, 48, 48, 0};
static const shape_t COIN_SHAPE = {8, 32, 32, 0};




#endif
