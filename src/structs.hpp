// Base in-game global structs
#pragma once

#include "include.hpp"
#include "dataLoader.hpp"
#include "entity.hpp"

struct App{
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_AudioDeviceID* stream;
};

// Data for creating fonts
extern Uint8* fontMemory;  // Memory with font data
extern uint64_t fontSize;  // Size of memory buffer

// Creating main varables
extern App app;  // Global main render and window

// All textures
extern SDL_Texture* Textures[IMG_count];  // Array of all textures

// All animations
extern IMG_Animation* Animations[ANI_count];  // Array of all animations

// All music trcks
//extern Mix_Music* Musics[MUS_count];  // Array of all music
//extern SDL_RWops* MusicsData[MUS_count];  // Array of data for music

// All effects sounds
//extern Mix_Chunk* Sounds[SND_count];  // Array of all sound effects

// Flags of running
extern bool running;  // Flag of main cycle work
extern bool game_over;  // Flag of showing loosing screen
extern bool advertisingMode;  // Mode of showing 'advertisment'

// Previous time
extern Uint16 lastBoostTicks;  // Ticks from boost activation

// Global entitys
extern Head player;
extern std::vector<Bullet> BulletArray;
extern std::vector<Mob> MobArray;
extern std::vector<Pow> PowArray;
