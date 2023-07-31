#include <string>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#define gridX 16
#define gridY 20

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 600
#define FPS 60

#define MOVING_TIME 50
#define POWERUP_TIME 5000
#define SHOOT_TIME 250
#define AsteroidsNumber 10

#define meteorCount 6
#define regularExplosionCount 9
#define sonicExplosionCount 8

// Names of images in array to using
enum IMG_names{
    IMG_player,
    IMG_laser,
    IMG_bolt,
    IMG_shield,
    IMG_background,
    IMG_meteor0,
    IMG_meteor1,
    IMG_meteor2,
    IMG_meteor3,
    IMG_meteor4,
    IMG_meteor5,
    IMG_regular_explosion0,
    IMG_regular_explosion1,
    IMG_regular_explosion2,
    IMG_regular_explosion3,
    IMG_regular_explosion4,
    IMG_regular_explosion5,
    IMG_regular_explosion6,
    IMG_regular_explosion7,
    IMG_regular_explosion8,
    IMG_sonic_explosion0,
    IMG_sonic_explosion1,
    IMG_sonic_explosion2,
    IMG_sonic_explosion3,
    IMG_sonic_explosion4,
    IMG_sonic_explosion5,
    IMG_sonic_explosion6,
    IMG_sonic_explosion7,
    IMG_slider_line,
    IMG_slider_button,
    IMG_flag_USA,
    IMG_flag_RUS,
    IMG_count
};
// Names of files to load textures
std::string IMG_files[IMG_count]{
    "img/playerShip1_orange.png",
    "img/laserRed16.png",
    "img/bolt_gold.png",
    "img/shield_gold.png",
    "img/starfield.png",
    "img/meteorBrown_big1.png",
    "img/meteorBrown_med1.png",
    "img/meteorBrown_med3.png",
    "img/meteorBrown_small1.png",
    "img/meteorBrown_small2.png",
    "img/meteorBrown_tiny1.png",
    "img/regularExplosion00.png",
    "img/regularExplosion01.png",
    "img/regularExplosion02.png",
    "img/regularExplosion03.png",
    "img/regularExplosion04.png",
    "img/regularExplosion05.png",
    "img/regularExplosion06.png",
    "img/regularExplosion07.png",
    "img/regularExplosion08.png",
    "img/sonicExplosion00.png",
    "img/sonicExplosion01.png",
    "img/sonicExplosion02.png",
    "img/sonicExplosion03.png",
    "img/sonicExplosion04.png",
    "img/sonicExplosion05.png",
    "img/sonicExplosion06.png",
    "img/sonicExplosion07.png",
    "img/slider_line.png",
    "img/slider_button.png",
    "img/Flag_USA.png",
    "img/Flag_RUS.png"
};

// Powerup types
enum POW_types{
    POW_bolt,
    POW_shield,
    POW_count
};

struct App{
    SDL_Renderer *renderer;
    SDL_Window *window;
};
App app;  // Creating main varables

// Flags of running
bool running = true;  // Flag of main cycle work
bool game_over = true;  // Flag of showing loosing screen

// Global numbers
int score = 0;
int oldShootTime = 0;
int oldMoveTime = 0;
bool Shooting = false;
int shield = 100;
int lives = 3;
int BoostTime = 0;
unsigned char MusicVolume = MIX_MAX_VOLUME/2;
unsigned char EffectsVolume = MIX_MAX_VOLUME/2;

SDL_Rect ShieldRectBack = {5, 5, 100, 10};  // Back part of health bar
SDL_Rect ShieldRectFront = {5, 5, 100, 10};  // Front part of health bar

SDL_Rect BoostRectBack = {5, 20, 100, 10};  // Back part of boost bar
SDL_Rect BoostRectFront = {5, 20, 100, 10};  // Front part of boost bar

// Texts variables and constants
SDL_Texture *Textures[IMG_count];  // Array of all textures
// Music and sound effects
Mix_Music* gMusic = NULL;
Mix_Chunk* gRegExpl = NULL;
Mix_Chunk* gSonExpl = NULL;
Mix_Chunk* gPew = NULL;
Mix_Chunk* gPowBolt = NULL;
Mix_Chunk* gPowShield = NULL;

// Static text on screen with drawing functions
class staticText
{
private:
    TTF_Font* Font;
    SDL_Surface *Surface;
    SDL_Texture *Texture;
    SDL_Rect Rect;
public:
    ~staticText(){
        SDL_FreeSurface(Surface);
        SDL_DestroyTexture(Texture);
        TTF_CloseFont(Font);
    }
    void set(std::string text, int size, SDL_Color color, int x, int y){
        Font = TTF_OpenFont("Arial.ttf", size);  // Reading font to drawing text
        Surface = TTF_RenderUTF8_Solid(Font, text.std::string::c_str(), color);
        Texture = SDL_CreateTextureFromSurface(app.renderer, Surface);
        SDL_QueryTexture(Texture, NULL, NULL, &Rect.w, &Rect.h);
        Rect.x = x - Rect.w/2; Rect.y = y;
    }
    void draw(){
        SDL_RenderCopy(app.renderer, Texture, NULL, &Rect);
    };
};

// Class of drawing dinamic text at screen
class dinamicText
{
private:
    TTF_Font* Font;
    SDL_Surface *Surface;
    SDL_Texture *Texture;
    SDL_Rect Rect;
public:
    dinamicText(int size, int x, int y){
        Font = TTF_OpenFont("Arial.ttf", size);  // Reading font to drawing text
        Rect.x = x; Rect.y = y;
    }
    ~dinamicText(){
        SDL_FreeSurface(Surface);
        SDL_DestroyTexture(Texture);
        TTF_CloseFont(Font);
    }
    void draw(std::string text, SDL_Color color){
        Surface = TTF_RenderText_Solid(Font, text.std::string::c_str(), color);
        Texture = SDL_CreateTextureFromSurface(app.renderer, Surface);
        SDL_QueryTexture(Texture, NULL, NULL, &Rect.w, &Rect.h);
        SDL_RenderCopy(app.renderer, Texture, NULL, &Rect);
    };
};

// Declaring static text
staticText TXT_SHMUP;
staticText TXT_KEYS;
staticText TXT_START;
staticText TXT_Pause;
staticText TXT_Music;
staticText TXT_Sound;

// Base in-game functions
// Function of loading all textures to array
void loadTextures(){
    SDL_Surface *temp_surface;
    for(int i = 0; i < IMG_count; ++i){
        //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", IMG_files[i]);
        temp_surface = IMG_Load(IMG_files[i].std::string::c_str());
        Textures[i] = SDL_CreateTextureFromSurface(app.renderer, temp_surface);
        SDL_FreeSurface(temp_surface);
    }
};

// Function clearing textures from RAM
void unloadTextures(){
    for(int i = 0; i < IMG_count; ++i){
        SDL_DestroyTexture(Textures[i]);
        Textures[i] = NULL;
    }
}

// Function of loading all media
void loadAudio(){
    gMusic = Mix_LoadMUS("snd/tgfcoder-FrozenJam-SeamlessLoop.ogg");
    gRegExpl = Mix_LoadWAV("snd/expl3.wav");
    gSonExpl = Mix_LoadWAV("snd/expl6.wav");
    gPew = Mix_LoadWAV("snd/pew.wav");
    gPowBolt = Mix_LoadWAV("snd/pow4.wav");
    gPowShield = Mix_LoadWAV("snd/pow5.wav");
}

// Function of unloading from RAM all media
void unloadAudio(){
    Mix_FreeMusic(gMusic);
    Mix_FreeChunk(gRegExpl);
    Mix_FreeChunk(gSonExpl);
    Mix_FreeChunk(gPew);
    Mix_FreeChunk(gPowBolt);
    Mix_FreeChunk(gPowShield);
}

// Function of getting collision of 2 objects
bool isCollide(SDL_Rect rect1, SDL_Rect rect2){
    return (
        ((rect1.y < rect2.y+rect2.h) &&
        (rect1.y+rect1.h > rect2.y))
        &&
        ((rect1.x < rect2.x+rect2.w) &&
        (rect1.x+rect1.w > rect2.x))
    );
}

// Game classes
// Base entity in-game class
class Entity{
public:
    int speedx, speedy;
    SDL_Texture *texture;
    SDL_Rect dest;
//public:
    Entity(){};
    ~Entity(){};
    void init();
    void blit(){
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	    SDL_RenderCopy(app.renderer, texture, NULL, &dest); 
    };
    void update(){
        dest.x += speedx; dest.y += speedy;
    };
};

class Head:public Entity
{
private:
    unsigned char frame;
public:
    void init(){
        texture = Textures[IMG_player];
    };
    void blit(){
	    SDL_RenderCopy(app.renderer, texture, NULL, &dest); 
    };
    void reset(){
        texture = Textures[IMG_player];
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        dest.h/=2; dest.w/=2;
        speedx = 0; speedy = 0;
        dest.x = SCREEN_WIDTH/2 - dest.w/2;
        dest.y = SCREEN_HEIGHT - 80;
        frame=0;
    };
    void update(){
        if(frame != 0){
            frame += 1;
            if(frame % 5 == 0){
                dest.x += dest.h/2; dest.y += dest.w/2;
                texture = Textures[frame/5];
                SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
                dest.w/=2; dest.h/=2;
                dest.x -= dest.h/2; dest.y -= dest.w/2;
            }
            if(frame/5 == IMG_sonic_explosion7){
                frame = 0;
                shield = 100;
                lives -= 1;
                if(lives <= 0){
                    game_over = true;
                }
                reset();
            }
        }
        else{
            dest.x += speedx; dest.y += speedy;
            if(dest.x+dest.w > SCREEN_WIDTH){
                dest.x=SCREEN_WIDTH-dest.w;
            }
            if(dest.x < 0){
                dest.x=0;
            }
        }
    }
    void setAnimation(){
        frame = IMG_sonic_explosion0*5;
        texture = Textures[frame/5];
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        dest.w/=2; dest.h/=2;
    }
    bool isAnimation(){
        return (frame == 0);
    }
    void shoot();
};
Head player;

class Bullet:public Entity
{
public:
    Bullet(int PosX, int PosY){  //Spawning 
        speedx = 0; speedy = -10;
        dest.x = PosX; dest.y = PosY;
        texture = Textures[IMG_laser];
    }
    bool isOver(){
        return dest.y < 0;
    }
};
std::vector<Bullet> BulletArray;

class Mob:public Entity
{
private:
    int rot=0; int dRot=0;
    unsigned char frame;
public:
    void init(){
        texture = Textures[IMG_meteor0];
    }
    void blit(){
        SDL_RenderCopyEx( app.renderer, texture, NULL, &dest, rot, NULL, SDL_FLIP_NONE );
    }
    void update(){
        if(frame != 0){
            frame += 1;
            if(frame % 4 == 0){
                dest.x += dest.h/2; dest.y += dest.w/2;
                texture = Textures[frame/4];
                SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
                dest.w/=2; dest.h/=2;
                dest.x -= dest.h/2; dest.y -= dest.w/2;
            }
            if(frame/4 == IMG_regular_explosion8){
                reset();
            }
        }
        else{
            dest.x += speedx; dest.y += speedy; rot += dRot;
        }
    };
    void reset(){
        texture = Textures[IMG_meteor0 + rand() % meteorCount];
        speedx = rand() % 6 - 3;
        speedy = rand() % 7 + 1;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        dest.y = -dest.h - rand() % 20; 
        dest.x = rand() % (SCREEN_WIDTH - dest.w);
        dRot = rand() % 16 - 8;
        frame = 0;
    }
    void setAnimation(){
        rot = 0;
        frame = IMG_regular_explosion0*4;
        texture = Textures[frame/4];
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        dest.w/=2; dest.h/=2;
    }
    bool isOver(){
        return (dest.y - dest.h > SCREEN_HEIGHT) || (dest.x > SCREEN_WIDTH) || (dest.x+dest.w < 0);
    }
    bool isAnimation(){
        return (frame == 0);
    }
    SDL_Rect getDest(){
        return dest;
    }
};
Mob MobArrays[AsteroidsNumber];

class Pow:public Entity
{
private:
    char type;
public:
    Pow(SDL_Rect position){  //Spawning 
        speedx = 0; speedy = 2;
        dest = position; 
        dest.x += dest.w/2; dest.y += dest.h/2;
        type = rand() % POW_count;
        texture = Textures[IMG_bolt + type];
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        dest.x -= dest.w/2; dest.y -= dest.h/2;
    }
    void activate(){
        switch (type)
        {
        case POW_bolt:
            BoostTime = SDL_GetTicks();
            Mix_PlayChannel(-1, gPowBolt, 0);
            break;
        case POW_shield:
            shield += rand() % 20 + 10;
            if(shield >= 100){
                shield = 100;
            }
            Mix_PlayChannel(-1, gPowShield, 0);
            break;
        default:
            break;
        }
    }
    bool isOver(){
        return dest.y > SCREEN_HEIGHT;
    }
};
std::vector<Pow> PowArray;

class Slider{
private:
    SDL_Texture *textureLine;
    SDL_Texture *textureButton;
    SDL_Rect destLine;
    SDL_Rect destButton;
public:
    Slider(int y){
        textureLine = Textures[IMG_slider_line];
        textureButton = Textures[IMG_slider_button];
        SDL_QueryTexture(textureLine, NULL, NULL, &destLine.w, &destLine.h);
        SDL_QueryTexture(textureButton, NULL, NULL, &destButton.w, &destButton.h);
        destLine.x = SCREEN_WIDTH/2-destLine.w/2; 
        destLine.y = y - destLine.h/2; 
        destButton.y = y - destButton.h/2;
    };
    void blit(unsigned char state){
        destButton.x = destLine.x + state - destButton.w/2;
	    SDL_RenderCopy(app.renderer, textureLine, NULL, &destLine);
        SDL_RenderCopy(app.renderer, textureButton, NULL, &destButton);
    };
    bool in(int x, int y){
        return ((x > destLine.x && x < destLine.x+destLine.w) &&
            (y > destLine.y && y < destLine.y+destLine.h));
    }
    int getX(){
        return destLine.x;
    }
};

class Button
{
private:
    SDL_Texture *texture;
    SDL_Rect dest;
public:
    Button(int x, int y, IMG_names textureIndex){
        texture = Textures[textureIndex];
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        dest.x = x - dest.w/2; 
        dest.y = y - dest.h/2;
    };
    void blit(){
	    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
    };
    bool in(int x, int y){
        return ((x > dest.x && x < dest.x+dest.w) &&
            (y > dest.y && y < dest.y+dest.h));
    }
};

void Head::shoot(){
    if(SDL_GetTicks() - oldShootTime > SHOOT_TIME){
        oldShootTime = SDL_GetTicks();
        if(SDL_GetTicks() - BoostTime < POWERUP_TIME){  // Creating double shoot 
            Bullet newBullet1(dest.x, dest.y);
            Bullet newBullet2(dest.x + dest.w, dest.y);
            BulletArray.push_back(newBullet1);
            BulletArray.push_back(newBullet2);
        }
        else{  // Creating normal shoot
            Bullet newBullet(dest.x + dest.w/2-6, dest.y);
            BulletArray.push_back(newBullet);
        }
        Mix_PlayChannel(-1, gPew, 0);  // Playing sound of shooting
    }
}
    
// Function of initialasing 
void initSDL()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);  // Initialising SDL libarary

	app.window = SDL_CreateWindow("Astroshuter on SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
	
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);  // Initialasing image library
    TTF_Init();  // Initialasing fonts library
    //Mix_Init(MIX_INIT_OGG | MIX_INIT_FLAC);
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
}
// Function of closing and deinitialasing all libraries and files
void cleanup(void)
{
    // Closing all outside libraries
	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);
	
    Mix_CloseAudio();
    Mix_Quit();
	SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}

// Pause menu
void pause(){
    // Creating pause text
    Slider MusicSlider(300);
    Slider SoundSlider(450);
    Button BtnFlagUSA(SCREEN_WIDTH/2 - 100, 140, IMG_flag_USA );
    Button BtnFlagRUS(SCREEN_WIDTH/2 + 100, 140, IMG_flag_RUS );

    SDL_Event event;
    bool waiting = true;
    bool MouseDown = false;
    char inBox = 0;
    while(waiting){  // Starting loop for waiting for start
        while( SDL_PollEvent(&event) != 0 ){
            if(event.type == SDL_QUIT){
                running = false;  // Exit from program
                waiting = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    waiting = false;  // Returning to game
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN){
                MouseDown = true;
            }
            if (event.type == SDL_MOUSEBUTTONUP){
                MouseDown = false; inBox = 0;
            }
        }
        // Getting mouse position
        int MouseX, MouseY;
        SDL_GetMouseState(&MouseX, &MouseY);
        if(MouseDown && inBox == 0){
            if(MusicSlider.in(MouseX, MouseY)){
                inBox = 1;
            }
            else if(SoundSlider.in(MouseX, MouseY)){
                inBox = 2;
            }
            else if(BtnFlagUSA.in(MouseX, MouseY)){
                inBox = 3;
            }
            else if(BtnFlagRUS.in(MouseX, MouseY)){
                inBox = 4;
            }
        }
        switch(inBox)
        {
        case 1:
            MusicVolume = (MouseX - MusicSlider.getX()) / 2;
            if(MouseX - MusicSlider.getX() < 0) MusicVolume = 0;
            if(MouseX - MusicSlider.getX() > 255) MusicVolume = 255;
            Mix_VolumeMusic(MusicVolume);  // Setting volume of music
            break;
        case 2:
            EffectsVolume = (MouseX - SoundSlider.getX()) / 2;
            if(MouseX - SoundSlider.getX() < 0) EffectsVolume = 0;
            if(MouseX - SoundSlider.getX() > 255) EffectsVolume = 255;
            Mix_Volume(-1, EffectsVolume);  // Setting volume of effects
            break;
        case 3:
            TXT_SHMUP.set("SHMUP!", 64, {255, 255, 255}, SCREEN_WIDTH/2, SCREEN_HEIGHT/4);
            TXT_KEYS.set("Arrow keys move, Space to fire", 22, {255, 255, 255}, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
            TXT_START.set("Press any key to begin", 18, {255, 255, 255}, SCREEN_WIDTH/2, SCREEN_HEIGHT*3/4);
            TXT_Pause.set("Game on pause", 30, {255, 255, 255}, SCREEN_WIDTH/2, 20);
            TXT_Music.set("Music", 22, {255, 255, 255}, SCREEN_WIDTH/2, 250);
            TXT_Sound.set("Sounds", 22, {255, 255, 255}, SCREEN_WIDTH/2, 400);
            SDL_SetWindowTitle(app.window, "Astroshuter on SDL");
            break;
        case 4:
            TXT_SHMUP.set("ШМАП!", 64, {255, 255, 255}, SCREEN_WIDTH/2, SCREEN_HEIGHT/4);
            TXT_KEYS.set("Стрелки для движения, пробел для стрельбы", 22, {255, 255, 255}, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
            TXT_START.set("Нажмите любую кнопку для продолжения", 18, {255, 255, 255}, SCREEN_WIDTH/2, SCREEN_HEIGHT*3/4);
            TXT_Pause.set("Игра на паузе", 30, {255, 255, 255}, SCREEN_WIDTH/2, 20);
            TXT_Music.set("Музыка", 22, {255, 255, 255}, SCREEN_WIDTH/2, 250);
            TXT_Sound.set("Звук", 22, {255, 255, 255}, SCREEN_WIDTH/2, 400);
            SDL_SetWindowTitle(app.window, "Астрошутер на SDL");
            break;
        default:
            break;
        }
        // Drawing
        SDL_RenderCopy(app.renderer, Textures[IMG_background], NULL, NULL);  // Drawing background at screen
        TXT_Pause.draw();  TXT_Music.draw(); TXT_Sound.draw();  // Showing extra text
        MusicSlider.blit(MusicVolume*2);  SoundSlider.blit(EffectsVolume*2);  // Drawing sliders
        BtnFlagUSA.blit();  BtnFlagRUS.blit();  // Drawing buttons
        SDL_RenderPresent(app.renderer);  // Blitting textures on screen
        SDL_Delay(1000 / FPS);  // Delaying time to decrease CPU loading
    }
}

// Main function
int main(int argv, char** args){
    initSDL();  // Initialasing of main SDL library
    loadTextures();  // Loading sprites to the game
    loadAudio();  // Loading music and sounds to the game

    // Initialasing constant start text 
    TXT_SHMUP.set("SHMUP!", 64, {255, 255, 255}, SCREEN_WIDTH/2, SCREEN_HEIGHT/4);
    TXT_KEYS.set("Arrow keys move, Space to fire", 22, {255, 255, 255}, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    TXT_START.set("Press any key to begin", 18, {255, 255, 255}, SCREEN_WIDTH/2, SCREEN_HEIGHT*3/4);
    TXT_Pause.set("Game on pause", 30, {255, 255, 255}, SCREEN_WIDTH/2, 20);
    TXT_Music.set("Music", 22, {255, 255, 255}, SCREEN_WIDTH/2, 250);
    TXT_Sound.set("Sounds", 22, {255, 255, 255}, SCREEN_WIDTH/2, 400);
    
    // Initialasing dinamic 
    dinamicText ScoreText(18, SCREEN_WIDTH/2, 10);

    // Initialasing all objects at screen
    player.init();
    for(int i=0; i< meteorCount; ++i){
        MobArrays[i].init();
    }

    // Music and sound part
    Mix_PlayMusic( gMusic, -1 );  // Infinit playing music
    Mix_Volume(-1, MIX_MAX_VOLUME / 3);  // Setting volume of effects
    Mix_VolumeMusic( MIX_MAX_VOLUME / 3);  // Setting volume of music

    SDL_Event event;
    // Main game cycle
	while(running)
	{
        // Showing loading screen
        if(game_over){
            // Clearing all unnecesary information
            BulletArray.clear();
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
            for(int i=0; i< meteorCount; ++i){
                MobArrays[i].reset();
            }
            // Resetting values
            game_over = false;
            oldShootTime = SDL_GetTicks();
            score = 0; lives = 3; shield = 100;
            BoostTime = -POWERUP_TIME;
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
        }

        if(SDL_GetTicks() - oldMoveTime > MOVING_TIME){  // Updating all objects once per need time
            player.update();
            if(Shooting){
                player.shoot();  // Player shooting
            }
            // Moving all objects
            for(int i=0; i< meteorCount; ++i){
                MobArrays[i].update();
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
            for(int i=0; i<meteorCount; ++i){
                if(MobArrays[i].isOver()){
                    MobArrays[i].reset();  // Resseting asteroids, if over edges
                }
            }
            // Collsions of the objects
            for(int i=0; i<BulletArray.size(); ++i){  // Getting collisons of bullets and asteroids
                for(int j=0; j<meteorCount; ++j){  // year, square(n), not optimal
                    if(MobArrays[j].isAnimation() && isCollide(BulletArray[i].dest, MobArrays[j].dest)){
                        score += MobArrays[j].dest.w;
                        BulletArray.erase(BulletArray.begin()+i);
                        Mix_PlayChannel(-1, gRegExpl, 0);
                        MobArrays[j].setAnimation();
                        if(rand() % 10 == 0){  // Random creating power up
                            Pow newPow(MobArrays[j].getDest());
                            PowArray.push_back(newPow);
                        }
                    }
                }
            }
            // Getting collsion os hip and other objects
            if(player.isAnimation()){
                // Collisons of ship and asteroids
                for(int i=0; i<meteorCount; ++i){
                    if(MobArrays[i].isAnimation() && isCollide(player.dest, MobArrays[i].dest)){
                        shield -= MobArrays[i].dest.w;
                        Mix_PlayChannel(-1, gSonExpl, 0);  // Playing sound of explosion of ship
                        MobArrays[i].setAnimation();  // Playing animation of explosion meteor
                        if(shield <= 0){
                            player.setAnimation();  // Playing animation of explosion ship
                        }
                    }
                }
                // Collision of ship and power ups
                for(int i=0; i<PowArray.size(); ++i){
                    if(isCollide(player.dest, PowArray[i].dest)){
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
        for(int i=0; i< AsteroidsNumber; ++i){
            MobArrays[i].blit();  // Drawing all asteroids at screen
        }
        for(int i=0; i<PowArray.size(); ++i){  // Drawing all power ups at screen
            PowArray[i].blit();
        }

        // Drawing text and icons at screen
        SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);  // Drawing shield bar
        SDL_RenderFillRect(app.renderer, &ShieldRectBack);  // White bar
        ShieldRectFront.w = shield;  // Setting width (health bar) 
        SDL_SetRenderDrawColor(app.renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(app.renderer, &ShieldRectFront);  // Green bar 

        if(SDL_GetTicks() - BoostTime < POWERUP_TIME){  // Drawing boost bar
            SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(app.renderer, &BoostRectBack);  // White bar
            BoostRectFront.w = ( 100 - ((SDL_GetTicks() - BoostTime) / 50) );  // Setting width (Boost bar) 
            SDL_SetRenderDrawColor(app.renderer, 0, 0, 255, 255);
            SDL_RenderFillRect(app.renderer, &BoostRectFront);  // Blue bar 
        }
        ScoreText.draw(std::to_string(score), {255, 255, 255});  // Drawing score at screen
        for(int i=0; i<lives; ++i){
            SDL_Rect dest = { SCREEN_WIDTH-100+30*i, 5, 24, 18};
	        SDL_RenderCopy(app.renderer, Textures[IMG_player], NULL, &dest); 
        }
        SDL_RenderPresent(app.renderer);  // Blitting textures on screen
		SDL_Delay(1000 / FPS);  // Delaying time to decrease CPU loading
	}
    // Cleaning all data
    unloadTextures();
    unloadAudio();
    cleanup();
	return 0;
    // Adding aboba
    // Editing aboba
    // Final aboba
}