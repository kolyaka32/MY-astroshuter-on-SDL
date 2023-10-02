#pragma once

#include "include.hpp"

// Names of music in array to use
enum MUS_names{
    MUS_main,  // Only song in game
    // Final counter 
    MUS_count
};

// Names of sound effects in array to use
enum SND_names{
    SND_laser,
    SND_bolt,
    SND_shield,
    // Explosions
    SND_regExplosion,
    SND_sonicExplosion,
    // Final counter 
    SND_count
};

// Load all music and effects
bool loadAllAudio();

// Load music track
void loadMusic(MUS_names number, std::string name);

// Load sound effct
void loadSound(SND_names number, std::string name);

// Function of unloading all audio
void unloadAllAudio();

