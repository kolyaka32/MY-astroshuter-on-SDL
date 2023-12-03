#pragma once

#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

// Load file with all data
void loadData(std::string fileName);

// Function of clearing all temporary data, loaded from arcieve
void unloadData();

// Archive values
#define PASSWORD NULL  // Archive password

// Used numerated numbers
#define ICO_count 1  // Number of icones for better count
#define FNT_count 1  // Number of fonts for better count

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
    IMG_meteor5,
    IMG_meteorSpecial,

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
    IMG_sonic_explosion8,

    // Final counter 
    IMG_count
};

#if MEME_MOD
    #define METEOR_COUNT 7
#else
    #define METEOR_COUNT 6
#endif

// Names of music in array to use
enum MUS_names{
    MUS_main,  // Main in-game song
    MUS_menu,  // Menu waiting song
    // Final counter 
    MUS_count
};

// Names of sound effects in array to use
enum SND_names{
    SND_laser,  // Sound of shooting
    SND_bolt,  // Sound of power-up
    SND_shield,  // Sound of shield adding
    // Explosions
    SND_regExplosion,
    SND_sonicExplosion,
    // Final counter 
    SND_count
};

// Names of animations in array to use
enum ANI_names{
    ANI_menu,  // Menu animation of maxwell cat
    ANI_adv,  // In game advertisment (of watermellon)

    // Final counter
    ANI_count
};
