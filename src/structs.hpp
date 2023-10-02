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

extern App app;  // Creating main varables

// All in-game textures
extern SDL_Texture* Textures[IMG_count];  // Array of all textures

// All music trcks
extern Mix_Music* Musics[MUS_count];  // Array of all music

// All effects sounds
extern Mix_Chunk* Sounds[SND_count];  // Array of all sound effects

// Flags of running
extern bool running;  // Flag of main cycle work
extern bool game_over;  // Flag of showing loosing screen

// Times
extern int oldShootTime;
extern int oldMoveTime;
extern int BoostTime;

// Global entitys
extern Head player;
extern std::vector<Bullet> BulletArray;
extern std::vector<Mob> MobArray;
extern std::vector<Pow> PowArray;
