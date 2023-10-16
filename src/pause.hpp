#pragma once

#include "baseHud.hpp"
#include "structs.hpp"

// Types of language
enum{
    STANDART_LNG,  // Standart type of language (english)
    ENGLISH_LNG,  // English language
    RUSSIAN_LNG  // Russian language
} LANGUAGE_types;

// Setting text of interface
void setEnglishText();
void setRussianText();

// Pause menu
void pause();

// Declaring static text
extern staticText TXT_SHMUP;
extern staticText TXT_KEYS;
extern staticText TXT_START;
extern staticText TXT_Pause;
extern staticText TXT_Music;
extern staticText TXT_Sound;
extern staticText MenuHighScore;
extern staticText MenuMaxScore;

#if ADVERTISMENT_MOD
extern Animation Advertisment;
#endif

// External values to save and load from settings file
extern Uint8 language;  // Language settings
extern Uint8 MusicVolume;  // Start volume of music
extern Uint8 EffectsVolume;  // Start volume of effects
extern Uint32 score;  // Current player score
extern Uint32 MaxScore;  // Maximal player score
extern Uint16 FPS;  // Setted frames per seconds