# Game "Astroshooter"
[![ru](https://img.shields.io/badge/lang-ru-green.svg)](https://github.com/kolyaka32/Astroshuter-on-SDL/blob/master/README-ru.md)

This repository contains sources files for shot-em-up game "Astroshooter", I made based on c++ using SDL3 libraries.

![Screenshot of game](/screenshots/game-main.png?raw=true)

## Installing of game to play
1. Download archieve from [releases](https://github.com/kolyaka32/Astroshuter-on-SDL/releases), unzip and run 'Astroshooter.exe'!
2. Also, you can build project by your own, for that watch point 'Instalation for own use'.


## Game
After game launch you should shoot destroy and avoid asteroids.
Only goal is to stay max time and get maximal score.
Also you can pick up power-ups for repairing ship or shoot double lasers.
Extra settings can found in file 'settings1.ini'


## Supported languages
* English
* Russian


![Screenshot of menu](/screenshots/game-menu-en.png?raw=true)


## Instalation for own use (windows)
1. Install C++ compiler (such as [MSYS2](https://www.msys2.org/#installation));
2. Install [Make](https://sourceforge.net/projects/gnuwin32/files/make/3.81/make-3.81.exe/download);
3. Install [CMake](https://sourceforge.net/projects/cmake.mirror/);
4. Download and extract external SDL libraries:
4.1. [SDL3](https://github.com/libsdl-org/SDL/releases);
4.2. [SDL3-image](https://github.com/libsdl-org/SDL_image/releases);
4.3. [SDL3-mixer](https://github.com/libsdl-org/SDL_mixer/releases);
4.4. [SDL3-ttf](https://github.com/libsdl-org/SDL_ttf/releases);
5. Extra library - libzip (build by your own), required:
5.1. [zlib](https://www.zlib.net/);
5.2. bzip (came with GNU);
5.3. [libzip itself](https://libzip.org/download/);
5.4. Build libzip using cmake to 'build/' folder;
5.5. Run 'make' and 'make install' at command line at builed folder (as administrator);
6. (Optional) Code editor [Visual Studio Code](https://code.visualstudio.com/download) (for better usage) (Recomended to use with plugins on c++ and cmake).


## Instalation for own use (unux systems)
1. Check availability of compilers[g++], [make] and [cmake];
2. Check availability of [git];
3. Install all necesery external libraries:
4. External SDL libraries ([SDL3](https://github.com/libsdl-org/SDL/releases), [SDL3-image](https://github.com/libsdl-org/SDL_image/releases), [SDL3-mixer](https://github.com/libsdl-org/SDL_mixer/releases), [SDL3-ttf](https://github.com/libsdl-org/SDL_ttf/releases));
5. External archieve library - libzip (build by you own), required: [libzip](https://libzip.org/download/);
6. (Optional) Code editor [Visual Studio Code](https://code.visualstudio.com/download) (for better usage).


## Prepaired sources
Sources with all builded libraries can be located at [releases](https://github.com/kolyaka32/Astroshuter-on-SDL/releases) (Development-kit).


## Used external libraries:
* https://github.com/libsdl-org/SDL
* https://github.com/libsdl-org/SDL_image
* https://github.com/libsdl-org/SDL_mixer
* https://github.com/libsdl-org/SDL_ttf
* https://github.com/libsdl-org/SDL_net
* https://github.com/nih-at/libzip
