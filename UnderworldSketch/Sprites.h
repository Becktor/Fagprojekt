#ifndef sprites_h
#define sprites_h

//#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>

#define LOAD_ASSETS()  GD.safeload("Sprites.GD2");
#define HEROW_HANDLE 0
#define HEROW_WIDTH 74
#define HEROW_HEIGHT 48
#define HEROW_CELLS 8
#define HEROA_HANDLE 1
#define HEROA_WIDTH 74
#define HEROA_HEIGHT 48
#define HEROA_CELLS 2
#define HEROD_HANDLE 2
#define HEROD_WIDTH 74
#define HEROD_HEIGHT 36
#define HEROD_CELLS 2
#define HEROB_HANDLE 3
#define HEROB_WIDTH 74
#define HEROB_HEIGHT 48
#define HEROB_CELLS 2
#define MINOC_HANDLE 4
#define MINOC_WIDTH 80
#define MINOC_HEIGHT 43
#define MINOC_CELLS 4
#define MINOD_HANDLE 5
#define MINOD_WIDTH 80
#define MINOD_HEIGHT 43
#define MINOD_CELLS 4
#define MINOW_HANDLE 6
#define MINOW_WIDTH 80
#define MINOW_HEIGHT 43
#define MINOW_CELLS 4
#define TILE_HANDLE 7
#define TILE_WIDTH 48
#define TILE_HEIGHT 48
#define TILE_CELLS 2
#define COIN_HANDLE 8
#define COIN_WIDTH 32
#define COIN_HEIGHT 32
#define COIN_CELLS 3
#define DOOR_HANDLE 9
#define DOOR_WIDTH 48
#define DOOR_HEIGHT 48
#define DOOR_CELLS 1
#define ATTACK 198432UL
#define ATTACK_LENGTH 1600
#define ATTACK_FREQ 8000
#define JUMP 200032UL
#define JUMP_LENGTH 1280
#define JUMP_FREQ 44100
#define EXIT 201312UL
#define EXIT_LENGTH 4000
#define EXIT_FREQ 8000
#define COIN 205312UL
#define COIN_LENGTH 8152
#define COIN_FREQ 44100
#define ASSETS_END 213464UL
static const shape_t HEROW_SHAPE = {0, 74, 48, 0};
static const shape_t HEROA_SHAPE = {1, 74, 48, 0};
static const shape_t HEROD_SHAPE = {2, 74, 36, 0};
static const shape_t HEROB_SHAPE = {3, 74, 48, 0};
static const shape_t MINOC_SHAPE = {4, 80, 43, 0};
static const shape_t MINOD_SHAPE = {5, 80, 43, 0};
static const shape_t MINOW_SHAPE = {6, 80, 43, 0};
static const shape_t TILE_SHAPE = {7, 48, 48, 0};
static const shape_t COIN_SHAPE = {8, 32, 32, 0};
static const shape_t DOOR_SHAPE = {9, 48, 48, 0};




#endif
