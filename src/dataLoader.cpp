#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

#include "dataLoader.hpp"

void dataLoader::expectCorrection(){
    if(SDL_ReadU8(dataFile) != 0){
        printf("Problems with data file");
        exit(8);
    }
    if(SDL_ReadU8(dataFile) != IMG_count){
        printf("Wrong count of images");
        exit(9);
    }
    if(SDL_ReadU8(dataFile) != MUS_count){
        printf("Wrong count of music");
        exit(10);
    }
    if(SDL_ReadU8(dataFile) != SND_count){
        printf("Wrong count of sounds");
        exit(11);
    }
    if(SDL_ReadU8(dataFile) != ANIM_count){
        printf("Wrong count of animations");
        exit(12);
    }
    if(SDL_ReadU8(dataFile) != 0){
        printf("Problems with data file");
        exit(8);
    }
};

void dataLoader::loadIcone(){
    Uint64 size = SDL_ReadLE64(dataFile);
    int* buf = (int*)malloc(size);
    SDL_RWread(dataFile, buf, size, 1);
    SDL_RWops* tempRW = SDL_RWFromMem(buf, size);
    SDL_Surface* icone = IMG_LoadICO_RW(tempRW);
    SDL_SetWindowIcon(app.window, icone);
    SDL_FreeSurface(icone);
    SDL_RWclose(tempRW);
    free(buf);
};

void dataLoader::loadImage(){
    for(int i=0; i<IMG_count; ++i){
        Uint64 size = SDL_ReadLE64(dataFile);
        int* buf = (int*)malloc(size);
        SDL_RWread(dataFile, buf, size, 1);
        SDL_RWops* tempRW = SDL_RWFromMem(buf, size);
        Textures[i] = SDL_CreateTextureFromSurface(app.renderer, IMG_LoadPNG_RW(tempRW));
        SDL_RWclose(tempRW);
        free(buf);
    }
};

void dataLoader::loadAnimation(){
    for(int i=0; i<ANIM_count; ++i){
        Uint64 size = SDL_ReadLE64(dataFile);
        int* buf = (int*)malloc(size);
        SDL_RWread(dataFile, buf, size, 1);
        SDL_RWops* tempRW = SDL_RWFromMem(buf, size);
        Animations[i] = IMG_LoadGIFAnimation_RW(tempRW);
        SDL_RWclose(tempRW);
        free(buf);
    }
};

void dataLoader::loadAudio(){
    /*for(int i=0; i<MUS_count; ++i){
        Uint64 size = SDL_ReadLE64(dataFile);
        char* buf = (char*)malloc(size);
        SDL_RWread(dataFile, buf, size, 1);
        SDL_RWops* tempRW = SDL_RWFromMem(buf, size);
        Musics[i] = Mix_LoadMUS_RW(tempRW, 1);
        free(buf);
        //Musics[i] = Mix_LoadMUSType_RW(tempRW, MUS_OGG, 0);
        
        //SDL_RWclose(tempRW);
        SDL_RWops* tempRW1 = SDL_RWFromFile("snd/mainTheme.ogg", "r");
        Musics[i] = Mix_LoadMUS_RW(tempRW1, 1);
    }*/
    SDL_RWops* tempRW1 = SDL_RWFromFile("mus/mainTheme.ogg", "r");
    Musics[MUS_main] = Mix_LoadMUSType_RW(tempRW1, MUS_OGG, 1);
    SDL_RWops* tempRW2 = SDL_RWFromFile("mus/menuTheme.ogg", "r");
    Musics[MUS_menu] = Mix_LoadMUSType_RW(tempRW2, MUS_OGG, 1);

    for(int i=0; i<SND_count;++i){
        Uint64 size = SDL_ReadLE64(dataFile);
        int* buf = (int*)malloc(size);
        SDL_RWread(dataFile, buf, size, 1);
        SDL_RWops* tempRW = SDL_RWFromMem(buf, size);
        Sounds[i] = Mix_LoadWAV_RW(tempRW, 0);
        SDL_RWclose(tempRW);
        free(buf);
    }
};

void dataLoader::loadFont(){
    fontData.size = SDL_ReadLE64(dataFile);
    fontData.fontMem = (char*)malloc(fontData.size);
    int size = SDL_RWread(dataFile, fontData.fontMem, fontData.size, 1);
};

void dataLoader::init(std::string name){
    dataFile = SDL_RWFromFile(name.std::string::c_str(), "r");
    expectCorrection();

    // Loading all data from file
    loadIcone();
    loadImage();
    loadAnimation();
    loadAudio();
    loadFont();

    // Closing file with data
    SDL_RWclose(dataFile);
};

void dataLoader::unload(){
    // Unloading data in reverce form from loading
    // Deliting font data
    free(fontData.fontMem);
    // Unloading sound effects
    for(int i=0; i < SND_count; ++i){
        Mix_FreeChunk(Sounds[i]);
    }
    // Unloading music effects
    for(int i=0; i < MUS_count; ++i){
        Mix_FreeMusic(Musics[i]);
    }
    // Unloading gif animations
    for(int i=0; i<ANIM_count;++i){
        IMG_FreeAnimation(Animations[i]);
    }
    // Unloading images
    for(int i = 0; i < IMG_count; ++i){
        SDL_DestroyTexture(Textures[i]);
        Textures[i] = NULL;
    }
};
