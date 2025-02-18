/*
 * Copyright (C) 2024-2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "include.hpp"
#include "dataLoader.hpp"
#include "entity.hpp"

// Base in-game global structs
struct App {
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_AudioDeviceID stream;
};

struct Sound {
    Uint8 *wav_data;
    Uint32 wav_data_len;
    SDL_AudioStream *stream;
    void play() {
        SDL_ClearAudioStream(stream);
        SDL_PutAudioStreamData(stream, wav_data, (int)wav_data_len);
    }
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

// All music tracks
extern Mix_Music* Musics[MUS_count];  // Array of all music
extern SDL_IOStream* MusicsData[MUS_count];  // Array of data for music

// All effects sounds
extern Mix_Chunk* Sounds[SND_count];  // Array of all sound effects

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
