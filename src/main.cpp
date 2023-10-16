
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
// Last time and previous ticks update
int oldMoveTime;
int oldTickTime;
Uint8 lastBoostTicks;  // Ticks from boost activation
// Pause and init settings
Uint8 language;
Uint8 MusicVolume;
Uint8 EffectsVolume;
Uint32 MaxScore;
Uint16 FPS;
Uint32 score = 0;
// Global running flags
bool running = true;
bool game_over = true;

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
staticText MenuHighScore;
staticText MenuMaxScore;

#if ADVERTISMENT_MOD
    Animation Advertisment({0, GAME_HEIGHT, SCREEN_WIDTH, ADV_HIGHT}, "img/ADV2.gif");
#endif

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
    setWindoIcone("img/Game.ico");  // Setting window icone

    // Interface initialisation
    dinamicText ScoreText(18, SCREEN_WIDTH/2, 10);
    Button esc(SCREEN_WIDTH - 24, 24, IMG_esc_button);
    #if ADVERTISMENT_MOD
        Animation MenuAdvertisment({96, SCREEN_HEIGHT-192, 288, 192}, "img/ADV1.gif");
    #endif
    Bar ShieldBar({20, 5, MAX_SHIELD, 10}, {0, 255, 0, 255}, IMG_shield);  // Shield/health bar
    Bar BoostBar({20, 20, 100, 10}, {0, 0, 255, 255}, IMG_bolt);  // Bar of the remaining boost time

    Mix_PlayMusic( Musics[MUS_main], -1 );  // Infinite playing music

    // Cycle variables
    SDL_Event event;
    bool Shooting;

	while(running)  // Main game cycle
	{
        // Showing loading screen
        if(game_over){
            Shooting = false;
            // Clearing all unnecesary information
            BulletArray.clear();
            PowArray.clear();
            if(MaxScore < score){  // Updating max score
                MaxScore = score;
            }

            // Starting loop for waiting for start
            bool waiting = true;

            while(waiting&&running){
                switch (language)  // Setting text of score, on whuch language selected
                {
                case STANDART_LNG:
                case ENGLISH_LNG:
                    MenuHighScore.set("Ваш последний счёт: " + std::to_string(score), 20, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*3/5);
                    MenuMaxScore.set("Ваш максимальный счёт: " + std::to_string(MaxScore), 20, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*3/5+24);
                    break;
                
                case RUSSIAN_LNG:
                    MenuHighScore.set("Your last score: " + std::to_string(score), 20, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*3/5);
                    MenuMaxScore.set("Your max score: " + std::to_string(MaxScore), 20, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*3/5+24);
                }

                while( SDL_PollEvent(&event) != 0 ){  // Getting events
                    switch (event.type)
                    {
                    case SDL_QUIT:
                        running = false;  // Exit from program
                        waiting = false;
                        break;
                    
                    case SDL_KEYDOWN:
                        waiting = false;
                        break;
                    
                    case SDL_MOUSEBUTTONDOWN:
                        int MouseX, MouseY;
                        SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position
                        if(esc.in(MouseX, MouseY)){  // Clicking on escape button
                            pause();
                        }
                    }
                    if(!running) break;  // Breaking main cycle, if necesary
                }
                // Drawing
                SDL_RenderCopy(app.renderer, Textures[IMG_background], NULL, NULL);  // Drawing background at screen
                TXT_SHMUP.draw();
                TXT_KEYS.draw();
                TXT_START.draw();
                if(score != 0){  // Drawing game and max score, if necesary
                    MenuHighScore.draw();
                    MenuMaxScore.draw();
                }

                esc.blit();
                #if ADVERTISMENT_MOD
                    MenuAdvertisment.blit();
                #endif
                SDL_RenderPresent(app.renderer);

                SDL_Delay( 1000/FPS );    // Delaying constant time between ticks to decrease CPU loading
            }
            if(!running) break;  // Breaking main cycle, if necesary
            MenuHighScore.clear();  
            MenuMaxScore.clear();
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
            switch (event.type){
            case SDL_QUIT:
                running = false;  // Exit from program
                break;

            case SDL_KEYDOWN:
                // Resseting field and next new generation
                if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a){
                    player.moveLeft();
                }
                if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d){
                    player.moveRight();
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
                break;
            
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT 
                || event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_d) {
                    player.stop();
                }
                if (event.key.keysym.sym == SDLK_SPACE){
                    Shooting = false;
                }
                break;
            
            case SDL_MOUSEBUTTONDOWN:
                int MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position
                if(esc.in(MouseX, MouseY)){  // Checking clicking on escape button
                    pause();
                }
                break;
            }
            if(!running) break;  // Breaking main cycle, if necesary
        }
        // Objects update
        if(SDL_GetTicks() - oldMoveTime > 1000/UPDATE_FPS){  // Updating all objects once per need time
            // Moving all objects
            player.update();
            if(Shooting){
                player.tryShoot();  // Player shooting
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
                    i--;
                }
            }
            for(int i=0; i<PowArray.size(); ++i){
                if(PowArray[i].isOver()){
                    PowArray.erase(PowArray.begin()+i);  // Deleting PowerUps, if over edges
                    i--;
                }
            }
            for(int i=0; i<MobArray.size(); ++i){
                if(MobArray[i].isOver()){
                    MobArray[i].reset();  // Resseting asteroids, if over edges
                    i--;
                }
            }
            // Collsions of the objects
            for(int i=0; i < BulletArray.size(); ++i){  // Getting collisons of bullets and asteroids
                for(int j=0; j < MobArray.size(); ++j){  // year, n^2, not optimal
                    if((MobArray[j].isAnimation()) && (SDL_HasIntersection(&BulletArray[i].dest, &MobArray[j].dest))){
                        // Explosion of meteor
                        score += MobArray[j].dest.w;  // Increasing global score
                        // Adding meteor for increassing difficulty
                        if( (MobArray.size() < MAX_NUM_METEOR) && (score/METEOR_ADD_SCORE + START_NUM_ASTEROID > MobArray.size()) ){  
                            MobArray.push_back(Mob());
                            MobArray[MobArray.size()-1].reset();
                        }
                        BulletArray.erase(BulletArray.begin()+i);  // Deliting bullet
                        i--;
                        Mix_PlayChannel(-1, Sounds[SND_regExplosion], 0);  // Sound of explosion
                        MobArray[j].setAnimation();
                        if(rand() % 10 == 0){  // Random creating of power-up
                            Pow newPow(MobArray[j].getDest());
                            PowArray.push_back(newPow);
                        }
                    }
                }
            }
            // Getting collsion of ship and other objects
            if(player.isAnimation()){
                // Collisons of ship and asteroids
                for(int i=0; i<MobArray.size(); ++i){
                    if(MobArray[i].isAnimation() && SDL_HasIntersection(&player.dest, &MobArray[i].dest)){
                        if(player.shield <= MobArray[i].dest.w / 2){
                            Shooting = false;
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
                // Collision of ship and power-ups
                for(int i=0; i<PowArray.size(); ++i){
                    if(SDL_HasIntersection(&player.dest, &PowArray[i].dest)){
                        PowArray[i].activate();
                        PowArray.erase(PowArray.begin()+i);  // Deleting power ups, if collide with player
                        i--;
                    }
                }
            }
            if(lastBoostTicks != 0){
                lastBoostTicks--;
            }
            oldMoveTime = SDL_GetTicks();
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
        ShieldBar.blit(player.shield);
        if(lastBoostTicks > 0){
            BoostBar.blit( 100 * lastBoostTicks / D_POWERUP_TICKS  );
        }

        ScoreText.draw(std::to_string(score), MIDLE_text);  // Drawing score at screen
        player.blitLives();  // Drawing lives of player at screen
        esc.blit();  // Drawing escape button on screen
        #if ADVERTISMENT_MOD
            Advertisment.blit();  // Drawing advertisment at bottom
        #endif
        
        SDL_RenderPresent(app.renderer);  // Blitting all objects on screen

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
        MenuAdvertisment.clear();
    #endif

    // Cleaning all data
    unloadAllAudio();
    unloadTextures();
    cleanup();
	return 0;
}