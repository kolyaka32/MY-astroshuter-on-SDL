#pragma once

#include "include.hpp"
#include "define.hpp"

// Names of images in array to using
enum IMG_names{
    // Interface
    IMG_background,  // Background image
    IMG_esc_button,
    // Pause interface
    IMG_slider_line,
    IMG_slider_button,
    IMG_flag_USA,
    IMG_flag_RUS,

    // Objects
    IMG_player,  // Player ship
    IMG_laser,  // Firing sprite

    // Meteors types
    IMG_meteor0,
    IMG_meteor1,
    IMG_meteor2,
    IMG_meteor3,
    IMG_meteor4,
    #if MEME_MOD
        IMG_meteorSpecial,
    #endif
    IMG_meteor5,

    // Powerups
    IMG_bolt,
    IMG_shield,

    // Meteor explosion animation
    IMG_regular_explosion0,
    IMG_regular_explosion1,
    IMG_regular_explosion2,
    IMG_regular_explosion3,
    IMG_regular_explosion4,
    IMG_regular_explosion5,
    IMG_regular_explosion6,
    IMG_regular_explosion7,
    IMG_regular_explosion8,

    // Player explosion animation
    IMG_sonic_explosion0,
    IMG_sonic_explosion1,
    IMG_sonic_explosion2,
    IMG_sonic_explosion3,
    IMG_sonic_explosion4,
    IMG_sonic_explosion5,
    IMG_sonic_explosion6,
    IMG_sonic_explosion7,

    // Final counter 
    IMG_count
};

//const unsigned char METEOR_COUNT = IMG_meteor5-IMG_meteor0; // Number of different images of meteors
#if MEME_MOD
    #define METEOR_COUNT 7
#else
    #define METEOR_COUNT 6
#endif

// Load all textures
bool loadAllTextures();

// Load texture file to array
void loadTexture(IMG_names number, std::string name);

// Function of unloading 
void unloadTextures();
