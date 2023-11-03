#include "stdio.h"
#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

#include "init.hpp"

// Function of initialasing all libraries
void initLibraries(){
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)){  // Initialising SDL libarary
        printf("Couldn't initialise SDL main library");
        exit(1);
    }
    if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)){  // Initializing image library
        printf("Couldn't initialize image library");
        exit(2);
    }
    if(TTF_Init()){  // Initializing fonts library
        printf("Couldn't initialize font library");
        exit(3);
    }
    if(!Mix_Init(MIX_INIT_OGG | MIX_INIT_FLAC)){  // Initializing audio library
        printf("Couldn't initialize audio library");
        exit(4);
    }
    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 )){  // Opening audio chanel
        printf("Couldn't open audio chanel");
        exit(5);
    }
}

// Function of creating window and renderer for outputing image
void createVideo(bool advEnb){
    app.window = SDL_CreateWindow(WINDOWNAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT + advEnb*ADV_HIGHT, 0);
    if(app.window == NULL){
        printf("Couldn't create window");
        exit(6);
    }
	app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
    if(app.renderer == NULL){
        printf("Couldn't create renderer");
        exit(7);
    }
}

void deleteVideo(){
	SDL_DestroyRenderer(app.renderer);  // Destroying renderer
	SDL_DestroyWindow(app.window);  // Destrying window
}

void exitLibraries(){
    // Closing all outside libraries
    Mix_CloseAudio();  // Closing audio player
    Mix_Quit();  // Closing mixer player
	TTF_Quit();  // Closing font library
    IMG_Quit();  // Closing image library
    SDL_Quit();  // Closing main sdl library
}
