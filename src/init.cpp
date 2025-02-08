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
        exit(ERR_SDL_FFT);
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
    // Openning audio chanel
    if(!Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 )){
        SDL_Log("Couldn't initialase audio chanel: %s", SDL_GetError());
        exit(ERR_INI_SND);
    }
}

// Function of deleting window and renders
void deleteVideo() {
    SDL_CloseAudioDevice(app.stream);
	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);
}

// Function of closing all outside libraries and files
void exitLibraries() {
    // Closing all outside libraries
	TTF_Quit();        // Closing font library
    SDL_Quit();        // Closing main sdl library
}
