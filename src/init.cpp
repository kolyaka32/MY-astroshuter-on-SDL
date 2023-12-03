#include "stdio.h"
#include "structs.hpp"
#include "init.hpp"

// Function of initialasing all libraries
void initLibraries(){
    // Initialising main SDL libarary
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)){  
        printf("Couldn't initialise SDL main library.\n");
        exit(ERR_SDL_SDL);
    }
    // Initializing image library
    if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)){
        printf("Couldn't initialize image library.\n");
        exit(ERR_SDL_IMG);
    }
    // Initializing fonts library
    if(TTF_Init()){
        printf("Couldn't initialize font library.\n");
        exit(ERR_SDL_FFT);
    }
    // Initializing audio library
    if(!Mix_Init(MIX_INIT_OGG | MIX_INIT_FLAC)){
        printf("Couldn't initialize audio library.\n");
        exit(ERR_SDL_SND);
    }
}

// Function of creating window and renderer for outputing image
void createVideo(){
    // Creating main game window
    app.window = SDL_CreateWindow(WINDOWNAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(app.window == NULL){
        printf("Couldn't create window.\n");
        exit(ERR_INI_WIN);
    }
    // Creating renderer from window
	app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
    if(app.renderer == NULL){
        printf("Couldn't create renderer.\n");
        exit(ERR_INI_REN);
    }
    // Openning audio chanel
    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 )){
        printf("Couldn't initialase audio chanel.\n");
        exit(ERR_INI_SND);
    }
}

// Function of deleting window and renders
void deleteVideo(){
    Mix_CloseAudio();                   // Closing audio library
	SDL_DestroyRenderer(app.renderer);  // Destroying renderer
	SDL_DestroyWindow(app.window);      // Destrying window
}

// Function of closing all outside libraries and files
void exitLibraries(){
    // Closing all outside libraries
    Mix_CloseAudio();  // Closing audio player
    Mix_Quit();        // Closing mixer player
	TTF_Quit();        // Closing font library
    IMG_Quit();        // Closing image library
    SDL_Quit();        // Closing main sdl library
}
