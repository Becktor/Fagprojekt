#define LOAD_ASSETS()  GD.safeload("Media.GD2");
#define SONICW_HANDLE 0
#define SONICW_WIDTH 42
#define SONICW_HEIGHT 45
#define SONICW_CELLS 8
#define SONICR0_HANDLE 8
#define SONICR0_WIDTH 46
#define SONICR0_HEIGHT 36
#define SONICR0_CELLS 4
#define TILE_HANDLE 12
#define TILE_WIDTH 48
#define TILE_HEIGHT 48
#define TILE_CELLS 1
#define COIN 48096UL
#define COIN_LENGTH 8152
#define COIN_FREQ 44100
#define ATTACK 56248UL
#define ATTACK_LENGTH 1600
#define ATTACK_FREQ 8000
#define LAUGH 57848UL
#define LAUGH_LENGTH 20000
#define LAUGH_FREQ 8000
#define EXIT 77848UL
#define EXIT_LENGTH 4000
#define EXIT_FREQ 8000
#define JUMP 81848UL
#define JUMP_LENGTH 1280
#define JUMP_FREQ 44100
#define ASSETS_END 83128UL
static const shape_t SONICW_SHAPE = {0, 42, 45, 0};
static const shape_t SONICR_SHAPE = {8, 46, 36, 0};
static const shape_t TILE_SHAPE = {12, 48, 48, 0};