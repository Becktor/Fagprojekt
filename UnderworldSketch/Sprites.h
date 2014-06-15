 #ifndef sprites_h
#define sprites_h

//#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>

#define LOAD_ASSETS()  GD.safeload("Sprites.GD2");
#define HERO_MOVE_HANDLE 0
#define HERO_MOVE_WIDTH 84
#define HERO_MOVE_HEIGHT 56
#define HERO_MOVE_CELLS 4
#define HERO_ATTACK_HANDLE 1
#define HERO_ATTACK_WIDTH 84
#define HERO_ATTACK_HEIGHT 56
#define HERO_ATTACK_CELLS 2
#define HERO_DUCK_HANDLE 2
#define HERO_DUCK_WIDTH 84
#define HERO_DUCK_HEIGHT 56
#define HERO_DUCK_CELLS 4
#define HERO_IDLE_HANDLE 3
#define HERO_IDLE_WIDTH 84
#define HERO_IDLE_HEIGHT 56
#define HERO_IDLE_CELLS 2
#define HERO_JUMP_HANDLE 4
#define HERO_JUMP_WIDTH 84
#define HERO_JUMP_HEIGHT 56
#define HERO_JUMP_CELLS 1
#define HERO_FALL_HANDLE 5
#define HERO_FALL_WIDTH 84
#define HERO_FALL_HEIGHT 56
#define HERO_FALL_CELLS 1
#define MINO_CHARGE_HANDLE 6
#define MINO_CHARGE_WIDTH 80
#define MINO_CHARGE_HEIGHT 43
#define MINO_CHARGE_CELLS 4
#define MINO_DYING_HANDLE 7
#define MINO_DYING_WIDTH 80
#define MINO_DYING_HEIGHT 43
#define MINO_DYING_CELLS 4
#define MINO_WALK_HANDLE 8
#define MINO_WALK_WIDTH 80
#define MINO_WALK_HEIGHT 43
#define MINO_WALK_CELLS 4
#define TILE_HANDLE 9
#define TILE_WIDTH 48
#define TILE_HEIGHT 48
#define TILE_CELLS 4
#define COIN_HANDLE 10
#define COIN_WIDTH 32
#define COIN_HEIGHT 32
#define COIN_CELLS 4
#define ATTACK 240896UL
#define ATTACK_LENGTH 1600
#define ATTACK_FREQ 8000
#define JUMP 242496UL
#define JUMP_LENGTH 944
#define JUMP_FREQ 8000
#define EXIT 243440UL
#define EXIT_LENGTH 4000
#define EXIT_FREQ 8000
#define COIN 247440UL
#define COIN_LENGTH 5104
#define COIN_FREQ 32000
#define ASSETS_END 252544UL
static const shape_t HERO_MOVE_SHAPE = {0, 84, 56, 0};
static const shape_t HERO_ATTACK_SHAPE = {1, 84, 56, 0};
static const shape_t HERO_DUCK_SHAPE = {2, 84, 56, 0};
static const shape_t HERO_IDLE_SHAPE = {3, 84, 56, 0};
static const shape_t HERO_JUMP_SHAPE = {4, 84, 56, 0};
static const shape_t HERO_FALL_SHAPE = {5, 84, 56, 0};
static const shape_t MINO_CHARGE_SHAPE = {6, 80, 43, 0};
static const shape_t MINO_DYING_SHAPE = {7, 80, 43, 0};
static const shape_t MINO_WALK_SHAPE = {8, 80, 43, 0};
static const shape_t TILE_SHAPE = {9, 48, 48, 0};
static const shape_t COIN_SHAPE = {10, 32, 32, 0};




#endif
