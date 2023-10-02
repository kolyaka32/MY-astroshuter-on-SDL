
#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

// Function of initialasing 
void initSDL()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);  // Initialising SDL libarary

	app.window = SDL_CreateWindow(WINDOWNAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
	
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);  // Initialasing image library
    TTF_Init();  // Initialasing fonts library
    Mix_Init(MIX_INIT_OGG | MIX_INIT_FLAC);
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
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
