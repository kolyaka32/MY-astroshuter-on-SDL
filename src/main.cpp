
#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

#include "init.hpp"
#include "dataLoader.hpp"
#include "baseHud.hpp"
#include "pause.hpp"
#include "initFile.hpp"
#include "entity.hpp"

#include "SDL3/SDL_main.h"

App app;  // Creating main varables

// Data for creating fonts
Uint8* fontMemory;    // Memory with font data
uint64_t fontSize;    // Size of memory buffer

// Global numbers
// Last time and previous ticks update
Uint64 oldMoveTime;
Uint64 oldDrawTime;
Uint16 lastBoostTicks;  // Ticks from boost activation
// Pause and init settings
Uint8 language;         // Switched languaged from language_types
float MusicVolume;      // Volume of music
float EffectsVolume;    // Volume of effects
Uint32 MaxScore;        // Max previous game score
Uint16 drawFPS;         // Max terget FPS to draw
Uint32 score;           // Game score

// Global running flags
bool running = true;    // Main cycle game flag of running
bool game_over = true;  // Flag of ending the round
bool advertisingMode;   // Mode of showing 'advertisment'

// Texts variables and constants
SDL_Texture* Textures[IMG_count];      // Array of all textures
IMG_Animation* Animations[ANI_count];  // Array of all animations
//Mix_Music* Musics[MUS_count];          // Array of all music
//SDL_RWops* MusicsData[MUS_count];      // Array of data for music
Sound Sounds[SND_count];  // Array of all sound effects

// Global statick texts
staticText texts[TXT_count];

// Global pseudo advertisment animation
Animation Advertisment({0, GAME_HEIGHT, SCREEN_WIDTH, ADV_HIGHT}, ANI_adv);

// Initialasing dinamic structures
Head player;
std::vector<Bullet> BulletArray;
std::vector<Mob> MobArray;
std::vector<Pow> PowArray;

// Main function
int main(int argv, char** args) {
    initLibraries();  // Initialasing all need libraries
    loadInitFile();   // Load initialasing file file with settings
    createVideo();    // Creating video output system
    
    // Loading data from file
    loadData("data1.dat");

    // Setting data from init file to program
    setInitData();

    // Interface initialisation
    dinamicText ScoreText(18, SCREEN_WIDTH/2, 10);
    Button esc(SCREEN_WIDTH - 24, 24, IMG_esc_button);
    Bar ShieldBar({20, 5, MAX_SHIELD, 10}, {0, 255, 0, 255}, IMG_shield);  // Shield/health bar
    Bar BoostBar({20, 20, 100, 10}, {0, 0, 255, 255}, IMG_bolt);  // Bar of the remaining boost time

    /*if (!advertisingMode) {
        Mix_PlayMusic( Musics[MUS_main], -1 );  // Infinite playing music without advertisment
    }*/

    // Cycle variables
    SDL_Event event;
    bool Shooting;

	while(running)  // Main game cycle
	{
        // Showing waiting start menu screen
        if (game_over) {
            Shooting = false;
            startMenu();
        }

        // Getting events
        while( SDL_PollEvent(&event) != 0 ) {  
            switch (event.type) {
            case SDL_EVENT_QUIT:
                running = false;  // Exit from program
                break;

            case SDL_EVENT_KEY_DOWN:
                // Resseting field and next new generation
                switch (event.key.key)
                {
                case SDLK_LEFT:
                case SDLK_A:
                    player.moveLeft();
                    break;

                case SDLK_RIGHT:
                case SDLK_D:
                    player.moveRight();
                    break;

                case SDLK_SPACE:
                    Shooting = true;
                    break;
                
                case SDLK_R:
                    game_over = true;
                    break;
                
                case SDLK_ESCAPE:
                    pause();
                }
                break;
            
            case SDL_EVENT_KEY_UP:
                switch (event.key.key)
                {
                case SDLK_LEFT:
                case SDLK_A:
                case SDLK_RIGHT:
                case SDLK_D:
                    player.stop();
                    break;

                case SDLK_SPACE:
                    Shooting = false;
                }
                break;
            
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                float MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position
                if (esc.in(MouseX, MouseY)) {  // Checking clicking on escape button
                    pause();
                }
                break;
            }
        }
        if (!running) break;  // Breaking main cycle, if necesary
        
        // Objects update
        if ( ((SDL_GetTicks() - oldMoveTime) > 1000 / UPDATE_FPS) ) {  // Updating all objects once per need time
            // Moving all objects
            player.update();
            if (Shooting) {
                player.tryShoot();  // Player shooting
            }
            for(int i=0; i< MobArray.size(); ++i) {
                MobArray[i].update();
            }
            for(int i=0; i<BulletArray.size(); ++i) {
                BulletArray[i].update();
            }
            for(int i=0; i<PowArray.size(); ++i) {
                PowArray[i].update();
            }
            // Deliting all unnececery objects
            for(int i=0; i<BulletArray.size(); ++i) {
                if (BulletArray[i].isOver()) {
                    BulletArray.erase(BulletArray.begin()+i);  // Deleting bullets, if over edges
                    i--;
                }
            }
            for(int i=0; i<PowArray.size(); ++i) {
                if (PowArray[i].isOver()) {
                    PowArray.erase(PowArray.begin()+i);  // Deleting PowerUps, if over edges
                    i--;
                }
            }
            for(int i=0; i<MobArray.size(); ++i) {
                if (MobArray[i].isOver()) {
                    MobArray[i].reset();  // Resseting asteroids, if over edges
                    i--;
                }
            }
            // Collsions of the objects
            for(int i=0; i < BulletArray.size(); ++i) {  // Getting collisons of bullets and asteroids
                for(int j=0; j < MobArray.size(); ++j) {  // year, n^2, not optimal
                    if ((MobArray[j].isAnimation()) && (SDL_HasRectIntersectionFloat(&BulletArray[i].dest, &MobArray[j].dest))) {
                        // Explosion of meteor
                        score += MobArray[j].dest.w;  // Increasing global score
                        // Adding meteor for increassing difficulty
                        if ( (MobArray.size() < MAX_NUM_METEOR) && (score/METEOR_ADD_SCORE + START_NUM_ASTEROID > MobArray.size()) ) {  
                            MobArray.push_back(Mob());
                            MobArray[MobArray.size()-1].reset();
                        }
                        BulletArray.erase(BulletArray.begin()+i);  // Deliting bullet
                        i--;
                        Sounds[SND_regExplosion].play();
                        MobArray[j].setAnimation();
                        if (rand() % 10 == 0) {  // Random creating of power-up
                            Pow newPow(MobArray[j].dest);
                            PowArray.push_back(newPow);
                        }
                    }
                }
            }
            // Getting collsion of ship and other objects
            if (player.isAnimation()) {
                // Collisons of ship and asteroids
                for(int i=0; i<MobArray.size(); ++i) {
                    if (MobArray[i].isAnimation() && SDL_HasRectIntersectionFloat(&player.dest, &MobArray[i].dest)) {
                        if (player.shield <= MobArray[i].dest.w / 2) {
                            Shooting = false;
                            player.setAnimation();  // Playing animation of explosion ship
                            player.shield = 100;
                        }
                        else{
                            player.shield -= MobArray[i].dest.w / 2;
                        }
                        Sounds[SND_sonicExplosion].play();
                        MobArray[i].setAnimation();  // Playing animation of explosion meteor
                    }
                }
                // Collision of ship and power-ups
                for(int i=0; i<PowArray.size(); ++i) {
                    if (SDL_HasRectIntersectionFloat(&player.dest, &PowArray[i].dest)) {
                        PowArray[i].activate();
                        PowArray.erase(PowArray.begin()+i);  // Deleting power ups, if collide with player
                        i--;
                    }
                }
            }
            if (lastBoostTicks != 0) {
                lastBoostTicks--;
            }
            oldMoveTime = SDL_GetTicks();
        }

        // Drawing all at screen
        if (SDL_GetTicks() - oldDrawTime > 1000 / drawFPS) {  // Checking, if drawing need
            SDL_RenderTexture(app.renderer, Textures[IMG_background], NULL, NULL);  // Drawing background at screen

            player.blit();  // Drawing player at screen
            for(int i=0; i<BulletArray.size(); ++i) {  // Drawing all bullets at screen
                BulletArray[i].blit();
            }
            for(int i=0; i < MobArray.size(); ++i) {
                MobArray[i].blit();  // Drawing all asteroids at screen
            }
            for(int i=0; i<PowArray.size(); ++i) {  // Drawing all power ups at screen
                PowArray[i].blit();
            }

            // Drawing text and icons at screen
            ShieldBar.blit(player.shield);
            if (lastBoostTicks > 0) {
                BoostBar.blit( 100 * lastBoostTicks / D_POWERUP_TICKS  );
            }

            ScoreText.draw(std::to_string(score), MIDLE_text);  // Drawing score at screen
            player.blitLives();  // Drawing lives of player at screen
            esc.blit();  // Drawing escape button on screen
            if (advertisingMode) {
                Advertisment.blit();  // Drawing advertisment at bottom
            }
            
            SDL_RenderPresent(app.renderer);  // Blitting all objects on screen

            oldDrawTime = SDL_GetTicks();  // Getting last update time
        };

        // Waiting until next moving or drawing
        Sint64 MoveSleep = ((SDL_GetTicks() - oldMoveTime) - 1000/UPDATE_FPS);
        Sint64 DrawSleep = ((SDL_GetTicks() - oldDrawTime) - 1000/drawFPS);
        SDL_Delay( MAX(MIN( MoveSleep, DrawSleep ), 0) );
	}
    // Exiting program
    saveInitFile();  // Saving all data to setting file for next start

    // Clearing static texts
    for(int i=0; i < TXT_count; ++i) {
        texts[i].clear();
    }
    // Clearing dinamic texts
    ScoreText.clear();

    // Clearing animations
    if (advertisingMode) {
        Advertisment.clear();
    }

    // Cleaning all data
    deleteVideo();
    unloadData();
    exitLibraries();
	return 0;
}