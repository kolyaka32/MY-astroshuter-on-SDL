#pragma once

#include "baseHud.hpp"
#include "structs.hpp"

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

// External values to save and load from settings file
extern unsigned char language;  // Language settings
extern unsigned char MusicVolume;  // Start volume of music
extern unsigned char EffectsVolume;  // Start volume of effects
