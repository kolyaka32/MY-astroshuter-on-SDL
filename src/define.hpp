#pragma once

// System numbers
#define WINDOWNAME "Astroshuter on SDL"
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 600
#define FPS 60

#define FONT_NAME "Arial.ttf"  // Main use font for drawing
#define MEME_MOD 0  // Activate meme include mode

// Balance options
#define MOVING_TIME 50
#define POWERUP_TIME 5000
#define SHOOT_TIME 250
#define START_NUM_ASTEROID 10
#define MAX_LIVES 3
#define MAX_SHIELD 100

#define LASER_SPEED 10
#define METEOR_ADD_SCORE 2000

// Number of animation frames
#define regularExplosionCount 9
#define sonicExplosionCount 8

// Powerup types
enum POW_types{
    POW_bolt,
    POW_shield,
    POW_count
};
