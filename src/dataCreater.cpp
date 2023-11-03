#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"
#include "init.hpp"

App app;

SDL_RWops* outData;  // File with all in-game data

void loadFileRW(std::string name){
    // Opening need file
    SDL_RWops* temp = SDL_RWFromFile(name.std::string::c_str(), "r");

    int size = SDL_RWsize(temp);
    int* buf = (int*)malloc(size);  // Creating buffer area for data
    SDL_RWread(temp, buf, size, 1);
    SDL_WriteLE64(outData, size);
    SDL_RWwrite(outData, buf, size, 1);  // Writing that data to main data file
    SDL_RWclose(temp);
    free(buf);
}

// Main game function
int main(int argv, char** args){
    initLibraries();  // Initialasing all need libraries

    outData = SDL_RWFromFile("data.dat", "w");  // Output file

    // Writing data
    // Writing numbers of count
    SDL_WriteU8(outData, 0);  // Writing seperator
    SDL_WriteU8(outData, IMG_count);  // Writing number of images
    SDL_WriteU8(outData, MUS_count);  // Writing number of music tracks
    SDL_WriteU8(outData, SND_count);  // Writing number of sound effects
    SDL_WriteU8(outData, ANIM_count);  // Writing number of animations
    SDL_WriteU8(outData, 0);

    // loading images
    // Loaing icone
    loadFileRW( "img/Game.ico");
    // Main unsigned pictures
    loadFileRW( "img/starfield.png");
    loadFileRW( "img/esc_button.png");
    loadFileRW( "img/slider_line.png");
    loadFileRW( "img/slider_button.png");
    loadFileRW( "img/Flag_USA.png");
    loadFileRW( "img/Flag_RUS.png");
    loadFileRW( "img/playerShip1_orange.png");
    loadFileRW( "img/laserRed16.png");
    // Meteors types
    loadFileRW( "img/meteorBrown_big1.png");
    loadFileRW( "img/meteorBrown_med1.png");
    loadFileRW( "img/meteorBrown_med3.png");
    loadFileRW( "img/meteorBrown_small1.png");
    loadFileRW( "img/meteorBrown_small2.png");
    loadFileRW( "img/meteorBrown_tiny1.png");
    // Mem mod
    loadFileRW( "img/raian-gosling-25.png");
    // Powerups
    loadFileRW( "img/bolt_gold.png");
    loadFileRW( "img/shield_gold.png");
    // Meteor explosion animation
    loadFileRW( "img/regularExplosion00.png");
    loadFileRW( "img/regularExplosion01.png");
    loadFileRW( "img/regularExplosion02.png");
    loadFileRW( "img/regularExplosion03.png");
    loadFileRW( "img/regularExplosion04.png");
    loadFileRW( "img/regularExplosion05.png");
    loadFileRW( "img/regularExplosion06.png");
    loadFileRW( "img/regularExplosion07.png");
    loadFileRW( "img/regularExplosion08.png");
    // Player explosion animation
    loadFileRW( "img/sonicExplosion00.png");
    loadFileRW( "img/sonicExplosion01.png");
    loadFileRW( "img/sonicExplosion02.png");
    loadFileRW( "img/sonicExplosion03.png");
    loadFileRW( "img/sonicExplosion04.png");
    loadFileRW( "img/sonicExplosion05.png");
    loadFileRW( "img/sonicExplosion06.png");
    loadFileRW( "img/sonicExplosion07.png");

    // Loading gif animations
    loadFileRW( "img/ADV1.gif");
    loadFileRW( "img/ADV2.gif");

    // Loading all music
    //loadFileRW( "snd/mainTheme.ogg");
    //loadFileRW( "snd/menuTheme.ogg");

    // Loading all effects
    loadFileRW( "snd/pew.wav");
    loadFileRW( "snd/pow4.wav");
    loadFileRW( "snd/pow5.wav");
    loadFileRW( "snd/expl3.wav");
    loadFileRW( "snd/expl6.wav");

    loadFileRW( "fonts/Arial.ttf");

    SDL_RWclose(outData);  // Closing main file

    // Cleaning all data
    deleteVideo();

    return 0;
}
