
#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

#include "init.hpp"
#include "images.hpp"
#include "audio.hpp"
#include "baseHud.hpp"
#include "pause.hpp"
#include "initFile.hpp"
#include "entity.hpp"

App app;  // Creating main varables

// Global numbers
unsigned int score;
int oldShootTime;
int oldMoveTime;
int BoostTime;
int oldTickTime;
// Pause and init settings
unsigned char language;
unsigned char MusicVolume;
unsigned char EffectsVolume;
//
bool running = true;
bool game_over = true;

const SDL_Rect ShieldRectBack = {5, 5, MAX_SHIELD, 10};  // Back part of health bar
SDL_Rect ShieldRectFront = {5, 5, MAX_SHIELD, 10};  // Front part of health bar

const SDL_Rect BoostRectBack = {5, 20, 100, 10};  // Back part of boost bar
SDL_Rect BoostRectFront = {5, 20, 100, 10};  // Front part of boost bar

// Texts variables and constants
SDL_Texture *Textures[IMG_count];  // Array of all textures
Mix_Music* Musics[MUS_count];  // Array of all music
Mix_Chunk* Sounds[SND_count];  // Array of all sound effects

// Global statick texts
staticText TXT_SHMUP;
staticText TXT_KEYS;
staticText TXT_START;
staticText TXT_Pause;
staticText TXT_Music;
staticText TXT_Sound;

// Initialasing dinamic structures
Head player;
std::vector<Bullet> BulletArray;
std::vector<Mob> MobArray;
std::vector<Pow> PowArray;

// Main function
int main(int argv, char** args){
    initSDL();  // Initialasing of main SDL library
    loadAllTextures();  // Loading sprites to the game
    loadAllAudio();  // Loading music and sounds to the game
    loadInitFile();  // Load initialasing file file with settings

    // Interface init
    dinamicText ScoreText(18, SCREEN_WIDTH/2, 10);
    Button esc(SCREEN_WIDTH - 24, 24, IMG_esc_button);
    #if ADVERTISMENT_MOD
        Animation Advertisment({0, GAME_HEIGHT, SCREEN_WIDTH, ADV_HIGHT}, "img/ADV.gif");
    #endif

    // initializing all objects at screen
    player.reset();
    MobArray.resize(START_NUM_ASTEROID);
    for(int i=0; i< MobArray.size(); ++i){
        MobArray[i].init();
    }

    Mix_PlayMusic( Musics[MUS_main], -1 );  // Infinite playing music

    // Cycle variables
    SDL_Event event;
    bool Shooting = false;

	while(running)  // Main game cycle
	{
        // Showing loading screen
        if(game_over){
            // Clearing all unnecesary information
            BulletArray.clear();
            PowArray.clear();
            // Showing extra text
            SDL_RenderCopy(app.renderer, Textures[IMG_background], NULL, NULL);  // Drawing background at screen
            TXT_SHMUP.draw();
            TXT_KEYS.draw();
            TXT_START.draw();
            SDL_RenderPresent(app.renderer);

            // Starting loop for waiting for start
            bool waiting = true;
            while(waiting){
                while( SDL_PollEvent(&event) != 0 ){
                    if(event.type == SDL_QUIT){
                        running = false;  // Exit from program
                        waiting = false;
                    }
                    if (event.type == SDL_KEYDOWN) {
                        waiting = false;
                    }
                }
                SDL_Delay(1000 / FPS);  // Delaying time to decrease CPU loading
            }
            // Resetting positions and speed of all objects
            player.reset();
            player.lives = MAX_LIVES; player.shield = MAX_SHIELD;
            MobArray.resize( START_NUM_ASTEROID);
            for(int i=0; i< MobArray.size(); ++i){
                MobArray[i].reset();
            }
            // Resetting values
            game_over = false;
            score = 0;
        }

        // Getting events
        while( SDL_PollEvent(&event) != 0 ){  
            if (event.type == SDL_QUIT){
                running = false;  // Exit from program
            }
            if (event.type == SDL_KEYDOWN) {
                // Resseting field and next new generation
                if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a){
                    player.speedx = -8;
                }
                if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d){
                    player.speedx = 8;
                }
                if (event.key.keysym.sym == SDLK_SPACE){
                    Shooting = true;
                }
                if (event.key.keysym.sym == SDLK_r){
                    game_over = true;
                }
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    pause();
                }
            }
            if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT 
                || event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_d) {
                    player.speedx = 0;
                }
                if (event.key.keysym.sym == SDLK_SPACE){
                    Shooting = false;
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN){
                // Getting mouse position
                int MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);
                if(esc.in(MouseX, MouseY)){  // Clicking on escape button
                    pause();
                }
            }
        }

        if(SDL_GetTicks() - oldMoveTime > MOVING_TIME){  // Updating all objects once per need time
            // Moving all objects
            player.update();
            if(Shooting && player.isAnimation()){
                player.shoot();  // Player shooting
            }
            for(int i=0; i< MobArray.size(); ++i){
                MobArray[i].update();
            }
            for(int i=0; i<BulletArray.size(); ++i){
                BulletArray[i].update();
            }
            for(int i=0; i<PowArray.size(); ++i){
                PowArray[i].update();
            }
            // Deliting all unnececery objects
            for(int i=0; i<BulletArray.size(); ++i){
                if(BulletArray[i].isOver()){
                    BulletArray.erase(BulletArray.begin()+i);  // Deleting bullets, if over edges
                }
            }
            for(int i=0; i<PowArray.size(); ++i){
                if(PowArray[i].isOver()){
                    PowArray.erase(PowArray.begin()+i);  // Deleting PowerUps, if over edges
                }
            }
            for(int i=0; i<MobArray.size(); ++i){
                if(MobArray[i].isOver()){
                    MobArray[i].reset();  // Resseting asteroids, if over edges
                }
            }
            // Collsions of the objects
            for(int i=0; i<BulletArray.size(); ++i){  // Getting collisons of bullets and asteroids
                for(int j=0; j<MobArray.size(); ++j){  // year, n^2, not optimal
                    if((MobArray[j].isAnimation()) && 
                    (SDL_HasIntersection(&BulletArray[i].dest, &MobArray[j].dest))){
                        // Explosion of meteor
                        score += MobArray[j].dest.w;  // Increasing global score
                        
                        if( score/METEOR_ADD_SCORE + START_NUM_ASTEROID > MobArray.size() ){  // Adding meteor for increassing difficulty
                            MobArray.push_back(Mob());
                            MobArray[MobArray.size()-1].reset();
                        }
                        BulletArray.erase(BulletArray.begin()+i);  // Deliting bullet
                        Mix_PlayChannel(-1, Sounds[SND_regExplosion], 0);  // Sound of explosion
                        MobArray[j].setAnimation();
                        if(rand() % 10 == 0){  // Random creating of power-up
                            Pow newPow(MobArray[j].getDest());
                            PowArray.push_back(newPow);
                        }
                    }
                }
            }
            // Getting collsion os hip and other objects
            if(player.isAnimation()){
                // Collisons of ship and asteroids
                for(int i=0; i<MobArray.size(); ++i){
                    if(MobArray[i].isAnimation() && SDL_HasIntersection(&player.dest, &MobArray[i].dest)){
                        if(player.shield <= MobArray[i].dest.w / 2){
                            player.setAnimation();  // Playing animation of explosion ship
                            player.shield = 100;
                        }
                        else{
                            player.shield -= MobArray[i].dest.w / 2;
                        }
                        Mix_PlayChannel(-1, Sounds[SND_sonicExplosion], 0);  // Playing sound of explosion of ship
                        MobArray[i].setAnimation();  // Playing animation of explosion meteor
                    }
                }
                // Collision of ship and power ups
                for(int i=0; i<PowArray.size(); ++i){
                    if(SDL_HasIntersection(&player.dest, &PowArray[i].dest)){
                        PowArray[i].activate();
                        PowArray.erase(PowArray.begin()+i);  // Deleting power ups, if collide with player
                    }
                }
            } 
        }
        // Drawing objects at screen
        SDL_RenderCopy(app.renderer, Textures[IMG_background], NULL, NULL);  // Drawing background at screen

        player.blit();  // Drawing player at screen
        for(int i=0; i<BulletArray.size(); ++i){  // Drawing all bullets at screen
            BulletArray[i].blit();
        }
        for(int i=0; i < MobArray.size(); ++i){
            MobArray[i].blit();  // Drawing all asteroids at screen
        }
        for(int i=0; i<PowArray.size(); ++i){  // Drawing all power ups at screen
            PowArray[i].blit();
        }

        // Drawing text and icons at screen
        SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);  // Drawing shield bar
        SDL_RenderFillRect(app.renderer, &ShieldRectBack);  // White bar
        ShieldRectFront.w = player.shield;  // Setting width (health bar) 
        SDL_SetRenderDrawColor(app.renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(app.renderer, &ShieldRectFront);  // Green bar 

        if(SDL_GetTicks() - BoostTime < POWERUP_TIME){  // Drawing boost bar if neccesary
            SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(app.renderer, &BoostRectBack);  // White bar
            BoostRectFront.w = ( 100 - ((SDL_GetTicks() - BoostTime) / 50) );  // Setting width (Boost bar) 
            SDL_SetRenderDrawColor(app.renderer, 0, 0, 255, 255);
            SDL_RenderFillRect(app.renderer, &BoostRectFront);  // Blue bar 
        }
        ScoreText.draw(std::to_string(score), MIDLE_text);  // Drawing score at screen
        player.blitLives();  // Drawing lives of player at screen
        esc.blit();  // Drawing escape button on screen
        #if ADVERTISMENT_MOD
            Advertisment.blit();  // Drawing advertisment at bottom
        #endif
        
        SDL_RenderPresent(app.renderer);  // Blitting textures on screen

        if( 1000/FPS > (SDL_GetTicks() - oldTickTime) ){  //
            SDL_Delay( 1000/FPS - (SDL_GetTicks() - oldTickTime) );  // Delaying constant time between ticks to decrease CPU loading
        }
        oldTickTime = SDL_GetTicks();  // Setting time of previous tick
	}
    // Exiting program
    saveInitFile();  // Saving all data to setting file for next start

    // Clearing dinamic structs
    ScoreText.clear();
    TXT_SHMUP.clear();
    TXT_KEYS.clear();
    TXT_START.clear();
    TXT_Pause.clear();
    TXT_Music.clear();
    TXT_Sound.clear();
    #if ADVERTISMENT_MOD
        Advertisment.clear();
    #endif

    // Cleaning all data
    unloadAllAudio();
    unloadTextures();
    cleanup();
	return 0;
}