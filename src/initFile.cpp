#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

#include "initFile.hpp"
#include "pause.hpp"

// Loading initialasing settings in game
void loadInitFile(){
    // Reading file
    std::ifstream in("settings.ini"); // Open file to read
    std::string line;  // Output string line

    language = 0;
    MusicVolume = MIX_MAX_VOLUME/2;
    EffectsVolume = MIX_MAX_VOLUME/2;
    MaxScore = 0;

    while(std::getline(in, line)){  // Reading file until it end
        std::string first = line.substr(0, line.find(' '));
        // Switching between options
        if( first == "language" ){
            std::string lang = line.substr(line.rfind(' ')+1);
            if(lang == "russian"){
                language = 1;
            }
            else if(lang == "english"){
                language = 2;
            }
        }
        else if( first == "music" ){
            MusicVolume = std::stoi( line.substr(line.rfind(' ')+1) );
        }
        else if( first == "effects" ){
            EffectsVolume = std::stoi( line.substr(line.rfind(' ')+1) );
        }
        else if( first == "maxScore" ){
            MaxScore = std::stoi( line.substr(line.rfind(' ')+1) );
        }
    }
    // Initialasing constant start text 
    switch (language)  // Setting up language
    {
    case 0:  // English language
    case 2:
        setEnglishText();
        break;
    case 1:  // Russian language
        setRussianText();
        break;
    default:
        break;
    }
    Mix_VolumeMusic(MusicVolume);  // Setting volume of music
    Mix_Volume(-1, EffectsVolume);  // Setting volume of effects

    in.close();  // Closing reading file
}

// Saving initialasing file
void saveInitFile(){
    std::ofstream setting("settings.ini");  // Creating output file

    // Writing data to output
    switch (language)  // Writing language
    {
    case 1:
        setting << "language = russian" << std::endl;
        break;
    case 0:
    case 2:
    default:
        setting << "language = english" << std::endl;
        break;
    }
    setting << "music = " << std::to_string(MusicVolume) << std::endl;  // Writing music volume
    setting << "effects = " << std::to_string(EffectsVolume) << std::endl;  // Writing effects volume
    setting << "maxScore = " << std::to_string(MaxScore) << std::endl;  // Writing max getting score

    setting.close();  // Closing file
}