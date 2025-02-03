#include "stdio.h"
#include "structs.hpp"
#include "init.hpp"

// Function of initialasing all libraries
void initLibraries(){
    // Initialising main SDL libarary
    if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)){  
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        exit(ERR_SDL_SDL);
    }
    // Initializing fonts library
    if(!TTF_Init()){
        printf("Couldn't initialize font library.\n");
        exit(ERR_SDL_FFT);
    }
}

// Function of creating window and renderer for outputing image
void createVideo(){
    // Setting application metadata
    SDL_SetAppMetadata("Astroshuter game", "1.0", "com.example.audio-multiple-streams");

    // Creating main game window
    if (!SDL_CreateWindowAndRenderer(WINDOWNAME, SCREEN_WIDTH, SCREEN_HEIGHT, 0, &app.window, &app.renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        exit(ERR_INI_REN);
    }
    // Openning audio chanel
    app.stream = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    if (app.stream == 0) {
        SDL_Log("Couldn't open audio device: %s", SDL_GetError());
        exit(ERR_INI_SND);
    }
}

// Function of deleting window and renders
void deleteVideo(){
    //Mix_CloseAudio();                   // Closing audio library
	SDL_DestroyRenderer(app.renderer);  // Destroying renderer
	SDL_DestroyWindow(app.window);      // Destrying window
}

// Function of closing all outside libraries and files
void exitLibraries(){
    // Closing all outside libraries
	TTF_Quit();        // Closing font library
    SDL_Quit();        // Closing main sdl library
}
