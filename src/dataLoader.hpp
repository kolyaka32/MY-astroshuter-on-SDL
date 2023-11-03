#pragma once

#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

class dataLoader
{
private:
    SDL_RWops* dataFile;
    void expectCorrection();  // Function of expecting correction of numbers
    void loadIcone();  // Loading game icone
    void loadImage();  // Loading all images
    void loadAnimation();  // Loading all GIF-animations
    void loadAudio();  // Loading all audio and music files
    void loadFont();  // Loading fonts 
public:
    void init(std::string name);  // Function of initialasing and loading data file
    void unload();
};


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
enum ANIM_types{
    ANIM_menu,  // Menu animation of maxwell cat
    ANIM_adv,  // In game advertisment (of watermellon)

    // Final counter
    ANIM_count
};
