#include "include.hpp"
#include "structs.hpp"
#include "audio.hpp"

// Counter of succsesful loadins
int AudioCnt;

// Load all music and effects
void loadAllAudio(){
    AudioCnt = 0;

    // Loading all music
    loadMusic(MUS_main, "snd/tgfcoder-FrozenJam-SeamlessLoop.ogg");

    // Loading all effects
    loadSound(SND_laser, "snd/pew.wav");
    loadSound(SND_bolt, "snd/pow4.wav");
    loadSound(SND_shield, "snd/pow5.wav");
    loadSound(SND_regExplosion, "snd/expl3.wav");
    loadSound(SND_sonicExplosion, "snd/expl6.wav");

    if(AudioCnt != SND_count + MUS_count){  // Checking corrction of number of loaded sounds
        printf("Couldn't load all necessary sounds");
        exit(9);
    }
}

// Load music track
void loadMusic(MUS_names number, std::string name){
    Musics[number] = Mix_LoadMUS((name).std::string::c_str());
    if(Musics[number] != NULL){
        AudioCnt+=1;
    }
}

// Load sound effct track
void loadSound(SND_names number, std::string name){
    Sounds[number] = Mix_LoadWAV((name).std::string::c_str());
    if(Sounds[number] != NULL){
        AudioCnt+=1;
    }
}

// Function of unloading all audio
void unloadAllAudio(){
    for(int i=0; i < MUS_count; ++i){
        Mix_FreeMusic(Musics[i]);
    }
    for(int i=0; i < SND_count; ++i){
        Mix_FreeChunk(Sounds[i]);
    }
}
