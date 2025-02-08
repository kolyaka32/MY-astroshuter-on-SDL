#include "include.hpp"
#include "structs.hpp"
#include "pause.hpp"

// Loading initialasing settings in game
void loadInitFile() {
    // Reading file
    std::ifstream in("settings1.ini"); // Open file to read
    std::string line;  // Output string line

    language = STANDART_LNG;
    musicVolume = MIX_MAX_VOLUME;
    effectsVolume = MIX_MAX_VOLUME;
    MaxScore = 0;
    drawFPS = BASE_FPS;
    advertisingMode = true;

    while(std::getline(in, line)) {  // Reading file until it end
        std::string first = line.substr(0, line.find(' '));
        // Switching between options
        if ( first == "language") {
            std::string lang = line.substr(line.rfind(' ')+1);
            if (lang == "russian") {
                language = RUSSIAN_LNG;
            }
            else if (lang == "english") {
                language = ENGLISH_LNG;
            }
        }
        else if ( first == "music") {
            musicVolume = std::stof(line.substr(line.rfind(' ') + 1))*MIX_MAX_VOLUME/100;
        }
        else if ( first == "effects") {
            effectsVolume = std::stof(line.substr(line.rfind(' ') + 1))*MIX_MAX_VOLUME/100;
        }
        else if ( first == "maxScore") {
            MaxScore = std::stoi( line.substr(line.rfind(' ') + 1));
        }
        else if ( first == "FPS") {
            drawFPS = std::stoi(line.substr(line.rfind(' ') + 1));
        }
        else if ( first == "advertising") {
            advertisingMode = std::stoi(line.substr(line.rfind(' ') + 1));
        }
    }
    in.close();  // Closing reading file
}

void setInitData() {
    // Initialasing constant start text 
    switch (language)  // Setting up language
    {
    case STANDART_LNG:  // English language
    case ENGLISH_LNG:
        setEnglishText();
        break;
    case RUSSIAN_LNG:  // Russian language
        setRussianText();
        break;
    }
    // Setting volumes of audio
    for (int i=0; i < SND_count; ++i) {
        Mix_VolumeChunk(Sounds[i], effectsVolume/2);
    }
    Mix_VolumeMusic(musicVolume/2);
}

// Saving initialasing file
void saveInitFile() {
    std::ofstream setting("settings1.ini");  // Creating output file

    // Writing data to output
    switch (language)  // Writing language
    {
    case STANDART_LNG:
    case ENGLISH_LNG:
    default:
        setting << "language = english" << std::endl;
        break;
    case RUSSIAN_LNG:
        setting << "language = russian" << std::endl;
        break;
    }
    setting << "music = " << std::to_string((int)SDL_roundf(musicVolume*100/MIX_MAX_VOLUME)) << std::endl;  // Writing music volume
    setting << "effects = " << std::to_string((int)SDL_roundf(effectsVolume*100/MIX_MAX_VOLUME)) << std::endl;  // Writing effects volume
    setting << "maxScore = " << std::to_string(MaxScore) << std::endl;  // Writing max getting score
    setting << "FPS = " << std::to_string(drawFPS) << std::endl;  // Writing frames per seconds
    setting << "advertising = " << std::to_string(advertisingMode);  // Writing state

    setting.close();  // Closing file
}
