#ifndef sprites_h
#define sprites_h

//#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>

#define LOAD_ASSETS()  GD.safeload("Sprites.GD2");
#define HERO_MOVING_HANDLE 0
#define HERO_MOVING_WIDTH 40
#define HERO_MOVING_HEIGHT 48
#define HERO_MOVING_CELLS 4
#define HERO_ATTACKING_HANDLE 1
#define HERO_ATTACKING_WIDTH 72
#define HERO_ATTACKING_HEIGHT 48
#define HERO_ATTACKING_CELLS 2
#define HERO_DUCKING_HANDLE 2
#define HERO_DUCKING_WIDTH 84
#define HERO_DUCKING_HEIGHT 28
#define HERO_DUCKING_CELLS 4
#define HERO_IDLE_HANDLE 3
#define HERO_IDLE_WIDTH 40
#define HERO_IDLE_HEIGHT 48
#define HERO_IDLE_CELLS 2
#define HERO_JUMPING_HANDLE 4
#define HERO_JUMPING_WIDTH 56
#define HERO_JUMPING_HEIGHT 48
#define HERO_JUMPING_CELLS 1
#define HERO_FALLING_HANDLE 5
#define HERO_FALLING_WIDTH 56
#define HERO_FALLING_HEIGHT 48
#define HERO_FALLING_CELLS 1
#define MINO_CHARGING_HANDLE 6
#define MINO_CHARGING_WIDTH 80
#define MINO_CHARGING_HEIGHT 43
#define MINO_CHARGING_CELLS 4
#define MINO_DYING_HANDLE 7
#define MINO_DYING_WIDTH 80
#define MINO_DYING_HEIGHT 43
#define MINO_DYING_CELLS 4
#define MINO_WALKING_HANDLE 8
#define MINO_WALKING_WIDTH 80
#define MINO_WALKING_HEIGHT 43
#define MINO_WALKING_CELLS 4
#define TILE_HANDLE 9
#define TILE_WIDTH 48
#define TILE_HEIGHT 48
#define TILE_CELLS 3
#define COIN_HANDLE 10
#define COIN_WIDTH 32
#define COIN_HEIGHT 32
#define COIN_CELLS 4
#define ATTACK 171008UL
#define ATTACK_LENGTH 1600
#define ATTACK_FREQ 8000
#define JUMP 172608UL
#define JUMP_LENGTH 944
#define JUMP_FREQ 8000
#define EXIT 173552UL
#define EXIT_LENGTH 4000
#define EXIT_FREQ 8000
#define COIN 177552UL
#define COIN_LENGTH 4072
#define COIN_FREQ 22050
#define ASSETS_END 181624UL
static const shape_t HERO_MOVING_SHAPE = {0, 40, 48, 0};
static const shape_t HERO_ATTACKING_SHAPE = {1, 72, 48, 0};
static const shape_t HERO_DUCKING_SHAPE = {2, 84, 28, 0};
static const shape_t HERO_IDLE_SHAPE = {3, 40, 48, 0};
static const shape_t HERO_JUMPING_SHAPE = {4, 56, 48, 0};
static const shape_t HERO_FALLING_SHAPE = {5, 56, 48, 0};
static const shape_t MINO_CHARGING_SHAPE = {6, 80, 43, 0};
static const shape_t MINO_DYING_SHAPE = {7, 80, 43, 0};
static const shape_t MINO_WALKING_SHAPE = {8, 80, 43, 0};
static const shape_t TILE_SHAPE = {9, 48, 48, 0};
static const shape_t COIN_SHAPE = {10, 32, 32, 0};

#endif
