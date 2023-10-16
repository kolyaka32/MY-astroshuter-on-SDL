// Base in-game global structs
#pragma once

#include "include.hpp"
#include "images.hpp"
#include "audio.hpp"
#include "entity.hpp"

struct App{
    SDL_Renderer *renderer;
    SDL_Window *window;
};

// Creating main varables
extern App app;  // Global main render and window

// All in-game textures
extern SDL_Texture* Textures[IMG_count];  // Array of all textures

// All music trcks
extern Mix_Music* Musics[MUS_count];  // Array of all music

// All effects sounds
extern Mix_Chunk* Sounds[SND_count];  // Array of all sound effects

// Flags of running
extern bool running;  // Flag of main cycle work
extern bool game_over;  // Flag of showing loosing screen

// Previous time
extern Uint8 lastBoostTicks;  // Ticks from boost activation

// Global entitys
extern Head player;
extern std::vector<Bullet> BulletArray;
extern std::vector<Mob> MobArray;
extern std::vector<Pow> PowArray;
