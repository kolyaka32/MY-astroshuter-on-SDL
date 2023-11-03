#pragma once

// Extra modifications for game
#define MEME_MOD true  // Activate meme include mode
#define ADV_HIGHT 70

// System numbers
#define WINDOWNAME "Astroshuter on SDL"
#define SCREEN_WIDTH 480
#define GAME_HEIGHT 600
#define SCREEN_HEIGHT GAME_HEIGHT
#define BASE_FPS 60
#define UPDATE_FPS 50

// Balance options
#define D_SHOOT_TICKS 12
#define D_POWERUP_TICKS 200
#define MAX_LIVES 3
#define MAX_SHIELD 100
#define LASER_SPEED 10
#define MOVE_SPEED 8

#define START_NUM_ASTEROID 10
#define METEOR_ADD_SCORE 2000
#define MAX_NUM_METEOR 40

// Number of animation frames
#define regularExplosionCount 9
#define sonicExplosionCount 8

// Powerup types
enum POW_types{
    POW_bolt,
    POW_shield,
    POW_count
};

// Macroses
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)