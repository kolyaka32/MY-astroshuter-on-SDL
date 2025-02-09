/*
 * Copyright (C) 2024-2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "stdio.h"
#include "structs.hpp"
#include "init.hpp"

// Function of initialasing all libraries
void initLibraries() {
    // Initialising main SDL libarary
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {  
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        exit(ERR_SDL_SDL);
    }
    // Initializing fonts library
    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize font library: %s", SDL_GetError());
        exit(ERR_SDL_TTF);
    }
    // Initializing audio library
    if (!Mix_Init(MIX_INIT_MP3 | MIX_INIT_WAVPACK)) {
        SDL_Log("Couldn't initialize audio library: %s", SDL_GetError());
        exit(ERR_SDL_AUD);
    }
}

// Function of creating window and renderer for outputing image
void createVideo() {
    // Setting application metadata
    SDL_SetAppMetadata("Astroshooter game", "1.2", NULL);

    // Creating main game window
    if (!SDL_CreateWindowAndRenderer(WINDOWNAME, SCREEN_WIDTH, SCREEN_HEIGHT, 0, &app.window, &app.renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        exit(ERR_INI_REN);
    }
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    // Openning audio chanel
    if(!Mix_OpenAudio(deviceId, NULL)){
        SDL_Log("Couldn't initialase audio chanel: %s", SDL_GetError());
        exit(ERR_INI_SND);
    }
}


void deleteVideo() {
    //Close mixer audio
    Mix_CloseAudio();
    SDL_CloseAudioDevice(app.stream);
	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);
}


void exitLibraries() {
    // Closing all outside libraries
    Mix_Quit();  // Closing audio library
	TTF_Quit();  // Closing font library
    SDL_Quit();  // Closing main sdl library
}
