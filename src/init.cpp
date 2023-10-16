#include "stdio.h"
#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"
#include "init.hpp"

// Function of initialasing all libraries
void initSDL()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)){  // Initialising SDL libarary
        printf("Couldn't initialise SDL main library");
        exit(1);
    }
	app.window = SDL_CreateWindow(WINDOWNAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(app.window == NULL){
        printf("Couldn't create window");
        exit(2);
    }
	app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
    if(app.renderer == NULL){
        printf("Couldn't create renderer");
        exit(3);
    }
    if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)){  // Initializing image library
        printf("Couldn't initialize image library");
        exit(4);
    }
    if(TTF_Init()){  // Initializing fonts library
        printf("Couldn't initialize font library");
        exit(5);
    }
    if(!Mix_Init(MIX_INIT_OGG | MIX_INIT_FLAC)){  // Initializing audio library
        printf("Couldn't initialize audio library");
        exit(6);
    }
    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 )){  // Opening audio chanel
        printf("Couldn't open audio chanel");
        exit(7);
    }
}

// Function of closing and deinitialasing all libraries and files
void cleanup()
{
    // Closing all outside libraries
	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);
	
    //Mix_CloseAudio();
    Mix_Quit();
	SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}

// Function of setting up icone of window
void setWindoIcone(std::string name){
    // Opening file with icone
    SDL_RWops* rwo = SDL_RWFromFile(name.std::string::c_str(), "r");
    SDL_Surface* icone = IMG_LoadICO_RW(rwo);
    if( rwo == NULL){
        printf("Couldn't load game icone: %s", name);
        exit(8);
    };

    SDL_SetWindowIcon(app.window, icone);
}