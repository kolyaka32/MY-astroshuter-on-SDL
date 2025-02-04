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

// Pause menu with settings
void pause();

// First loaded menu and game start waiting screen
void startMenu();

// Types of numerated static texts
enum TXT_types{
    // Menu texts
    TXT_MENU_SHMUP,
    TXT_MENU_KEYS,
    TXT_MENU_START,
    // Menu extra texts about score
    TXT_MENU_SCORE,
    TXT_MENU_HIGH_SCORE,
    // Pause texts
    TXT_PAUSE_PAUSE,
    TXT_PAUSE_MUSIC,
    TXT_PAUSE_SOUND,

    // Count of all texts
    TXT_count
};

// Declaring static text
extern staticText texts[TXT_count];
extern Animation Advertisment;

// External values to save and load from settings file
extern Uint8 language;  // Language settings
extern float MusicVolume;  // Start volume of music
extern float EffectsVolume;  // Start volume of effects
extern Uint32 score;  // Current player score
extern Uint32 MaxScore;  // Maximal player score
extern Uint16 drawFPS;  // Setted frames per seconds
