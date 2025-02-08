#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

#include "zip.h"

#include "init.hpp"
#include "dataLoader.hpp"

// Arcieve local structs
static zip_t* archive;  // Archive with all data

// Counters of loaded files
static Uint8 loadedImages;
static Uint8 loadedAnimations;
static Uint8 loadedMusics;
static Uint8 loadedSounds;

// Function of open archive and setting base password
zip_t* openarchive(const char* archiveName) {
    // Open archive with need name
    archive = zip_open(archiveName, ZIP_RDONLY, NULL);

    #if PASSWORD
    zip_set_default_password(archive, PASSWORD);
    #endif

    // Returning archive for checking correction
    return archive;
};

// Function of getting data of archive file
static inline SDL_IOStream* dataFromarchive(const char* name) {
    // Openning need file
    zip_file_t* file = zip_fopen_encrypted(archive, name, 0, PASSWORD);
    
    zip_stat_t st;
	zip_stat(archive, name, 0, &st);  // Getting parameters of current file
    // Checking correction of file
    if (st.size == 0) {  
        return NULL;
    }

    // Copping data to buffer
    char* buffer = new char[st.size];
    zip_fread(file, buffer, st.size);
    zip_fclose(file);
    // Creating SDL-based structure with data
    SDL_IOStream* tempRW = SDL_IOFromConstMem(buffer, st.size);

    // Returning created data structure
    return tempRW;
};

// Functions of loading objects
// Function of loading game icone
static unsigned loadIcone(const char* name) {
    // Getting icone data
    SDL_IOStream* tempRW = dataFromarchive(name);

    // Setting window icone
    SDL_Surface* iconeImage = IMG_LoadICO_IO(tempRW);
    if (iconeImage == NULL) {  // Checking creating image
        return 0;  // Returning 0 as error with loading
    }
    SDL_CloseIO(tempRW);
    SDL_SetWindowIcon(app.window, iconeImage);
    SDL_DestroySurface(iconeImage);
    return ICO_count;  // Returning correction of loading
};

// Functions of loading selected image file
static void loadPicture(const char* name, IMG_names number) {
    // Getting selected picture data
    SDL_IOStream* tempRW = dataFromarchive(name);
    // Creating texture from data
    Textures[number] = IMG_LoadTexture_IO(app.renderer, tempRW, true);

    // Checking correction of loaded file
    if (Textures[number] != NULL) {
        loadedImages++;
    };
};

// Function of loading selected GIF animation
static void loadAnimation(const char* name, ANI_names number) {
    // Getting selected animation data
    SDL_IOStream* tempRW = dataFromarchive(name);
    // Creating animation from data
    Animations[number] = IMG_LoadAnimation_IO(tempRW, 0);
    SDL_CloseIO(tempRW);

    // Checking correction of loaded file
    if (Animations[number] != NULL) {
        loadedAnimations++;
    };
};

// Function of loading selected music file
static void loadMusic(const char* name, MUS_names number) {
    // Getting selected music track data
    MusicsData[number] = dataFromarchive(name);
    // Creating music track from data
    Musics[number] = Mix_LoadMUS_IO(MusicsData[number], 0);

    // Checking correction of loaded file
    if (Musics[number] != NULL) {
        loadedMusics++;
    };
};

// Function of loading selected sound
static void loadSound(const char* name, SND_names number) {
    // Getting selected sound data
    SDL_IOStream* tempRW = dataFromarchive(name);
    // Creating sound from data
    Sounds[number] = Mix_LoadWAV_IO(tempRW, 1);

    // Checking correction of loaded file
    if(Sounds[number] != NULL){
        loadedSounds++;
    };
};

// Function of loading font
static unsigned loadFont(const char* name) {
    // Openning font file
    zip_file_t* file = zip_fopen_encrypted(archive, name, 0, PASSWORD);
    
    zip_stat_t st;
	zip_stat(archive, name, 0, &st);  // Getting data from file
    // Checking correction of file
    if (st.size == 0) {  
        return 0;
    }

    // Copping data to buffer
    fontMemory = new Uint8[st.size];
    fontSize = st.size;
    zip_fread(file, fontMemory, st.size);
    zip_fclose(file);

    // Checking correction
    return FNT_count;
};

// Functions of loading objects from lists
// Loading all images
static unsigned loadAllImages() {
    loadedImages = 0;  // Resseting counter
    //loadPicture("img/.png", IMG_);

    loadPicture("img/starfield.png", IMG_background);
    loadPicture("img/esc_button.png", IMG_esc_button);
    loadPicture("img/slider_line.png", IMG_slider_line);
    loadPicture("img/slider_button.png", IMG_slider_button);
    loadPicture("img/Flag_USA.png", IMG_flag_USA);
    loadPicture("img/Flag_RUS.png", IMG_flag_RUS);
    loadPicture("img/playerShip1_orange.png", IMG_player);
    loadPicture("img/laserRed16.png", IMG_laser);
    loadPicture("img/meteorBrown_big1.png", IMG_meteor0);
    loadPicture("img/meteorBrown_med1.png", IMG_meteor1);
    loadPicture("img/meteorBrown_med3.png", IMG_meteor2);
    loadPicture("img/meteorBrown_small1.png", IMG_meteor3);
    loadPicture("img/meteorBrown_small2.png", IMG_meteor4);
    loadPicture("img/meteorBrown_tiny1.png", IMG_meteor5);
    loadPicture("img/raian-gosling-25.png", IMG_meteorSpecial);
    loadPicture("img/bolt_gold.png", IMG_bolt);
    loadPicture("img/shield_gold.png", IMG_shield);
    loadPicture("img/regularExplosion00.png", IMG_regular_explosion0);
    loadPicture("img/regularExplosion01.png", IMG_regular_explosion1);
    loadPicture("img/regularExplosion02.png", IMG_regular_explosion2);
    loadPicture("img/regularExplosion03.png", IMG_regular_explosion3);
    loadPicture("img/regularExplosion04.png", IMG_regular_explosion4);
    loadPicture("img/regularExplosion05.png", IMG_regular_explosion5);
    loadPicture("img/regularExplosion06.png", IMG_regular_explosion6);
    loadPicture("img/regularExplosion07.png", IMG_regular_explosion7);
    loadPicture("img/regularExplosion08.png", IMG_regular_explosion8);
    loadPicture("img/sonicExplosion00.png", IMG_sonic_explosion0);
    loadPicture("img/sonicExplosion01.png", IMG_sonic_explosion1);
    loadPicture("img/sonicExplosion02.png", IMG_sonic_explosion2);
    loadPicture("img/sonicExplosion03.png", IMG_sonic_explosion3);
    loadPicture("img/sonicExplosion04.png", IMG_sonic_explosion4);
    loadPicture("img/sonicExplosion05.png", IMG_sonic_explosion5);
    loadPicture("img/sonicExplosion06.png", IMG_sonic_explosion6);
    loadPicture("img/sonicExplosion07.png", IMG_sonic_explosion7);
    loadPicture("img/sonicExplosion08.png", IMG_sonic_explosion8);

    // Returning numbers of loaded files
    return loadedImages;
};

// Loading all animations
static unsigned loadAllAnimations() {
    loadedAnimations = 0;  // Resseting counter
    //loadAnimation("ani/.gif", ANI_);
    loadAnimation("ani/ADV1.gif", ANI_menu);
    loadAnimation("ani/ADV2.gif", ANI_adv);

    // Returning numbers of loaded files
    return loadedAnimations;
};

// Loading all music tracks
static unsigned loadAllMusic() {
    loadedMusics = 0;  // Resseting counter
    //loadMusic("mus/.mp3", MUS_);
    loadMusic("mus/mainTheme.mp3", MUS_main);
    loadMusic("mus/menuTheme.mp3", MUS_menu);

    // Returning numbers of loaded files
    return loadedMusics;
};

// Loading all sounds
static unsigned loadAllSounds() {
    loadedSounds = 0;  // Resseting counter
    //loadSound("snd/.wav", SND_);

    loadSound("snd/pew.wav", SND_laser);
    loadSound("snd/pow4.wav", SND_bolt);
    loadSound("snd/pow5.wav", SND_shield);
    loadSound("snd/expl6.wav", SND_regExplosion);
    loadSound("snd/expl3.wav", SND_sonicExplosion);

    // Returning numbers of loaded files
    return loadedSounds;
};

void loadData(const char* fileName) {
    // Opening archive
    if (openarchive(fileName) == NULL) {
        SDL_Log("Can't load archieve: %s", SDL_GetError());
        exit(ERR_FIL_OPN);
    }  

    // Loading data from archive
    if (loadIcone("img/Game.ico") != ICO_count) {
        printf("Can't load game icone: %s", SDL_GetError());
        exit(ERR_FIL_ICO);
    }
    if (loadAllImages() != IMG_count) {
        printf("Wrong count of images: %s", SDL_GetError());
        exit(ERR_FIL_IMG);
    }
    if (loadAllAnimations() != ANI_count) {
        printf("Wrong count of animations: %s", SDL_GetError());
        exit(ERR_FIL_ANI);
    }
    if (loadAllMusic() != MUS_count) {
        printf("Wrong count of music: %s", SDL_GetError());
        exit(ERR_FIL_MUS);
    }
    if (loadAllSounds() != SND_count) {
        printf("Wrong count of sounds: %s", SDL_GetError());
        exit(ERR_FIL_SND);
    }
    if (loadFont("fnt/Arial.ttf") != FNT_count) {
        printf("Can't load font: %s", SDL_GetError());
        exit(ERR_FIL_FNT);
    }

    // Closing archive
    zip_close(archive);
}

// Function of clearing all temporary data, loaded from arcieve
void unloadData() {
    // Unloading data in reverce form from loading

    // Deliting font data
    free(fontMemory);
    // Unloading sound effects
    for(int i=0; i < SND_count; ++i) {
        Mix_FreeChunk(Sounds[i]);
    }
    // Unloading music effects and data
    for(int i=0; i < MUS_count; ++i) {
        Mix_FreeMusic(Musics[i]);
        SDL_CloseIO(MusicsData[i]);
    }
    // Unloading gif animations
    for(int i=0; i < ANI_count; ++i) {
        IMG_FreeAnimation(Animations[i]);
    }
    // Unloading images
    for(int i = 0; i < IMG_count; ++i) {
        SDL_DestroyTexture(Textures[i]);
        Textures[i] = NULL;
    }
};
