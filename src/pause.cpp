#include "include.hpp"
#include "define.hpp"
#include "pause.hpp"

// Types of selected box
enum{  
    NORMAL_BOX,
    MUSIC_SLIDER_BOX,
    EFFECT_SLIDER_BOX,
    ENGLISH_BOX,
    RUSSIAN_BOX,
} SELCTED_BOX_types;

void setEnglishText() {
    texts[TXT_MENU_SHMUP].set("SHMUP!", 64, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT/5);
    texts[TXT_MENU_KEYS].set("Arrow keys move, Space to fire", 22, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*2/5);
    texts[TXT_MENU_START].set("Press any key to begin", 18, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*2/5+70);
    texts[TXT_PAUSE_PAUSE].set("Game on pause", 30, MIDLE_text, SCREEN_WIDTH/2, 20);
    texts[TXT_PAUSE_MUSIC].set("Music", 22, MIDLE_text, SCREEN_WIDTH/2, 250);
    texts[TXT_PAUSE_SOUND].set("Sounds", 22, MIDLE_text, SCREEN_WIDTH/2, 400);
    texts[TXT_MENU_SCORE].set("Your last score: " + std::to_string(score), 20, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*3/5);
    texts[TXT_MENU_HIGH_SCORE].set("Your max score: " + std::to_string(MaxScore), 20, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*3/5+24);
    SDL_SetWindowTitle(app.window, "Astroshooter on SDL");
};

void setRussianText() {
    texts[TXT_MENU_SHMUP].set("ШМАП!", 64, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT/5);
    texts[TXT_MENU_KEYS].set("Стрелки для движения, пробел для стрельбы", 22, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*2/5);
    texts[TXT_MENU_START].set("Нажмите любую кнопку для продолжения", 18, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*2/5+70);
    texts[TXT_PAUSE_PAUSE].set("Игра на паузе", 30, MIDLE_text, SCREEN_WIDTH/2, 20);
    texts[TXT_PAUSE_MUSIC].set("Музыка", 22, MIDLE_text, SCREEN_WIDTH/2, 250);
    texts[TXT_PAUSE_SOUND].set("Звук", 22, MIDLE_text, SCREEN_WIDTH/2, 400);
    texts[TXT_MENU_SCORE].set("Ваш последний счёт: " + std::to_string(score), 20, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*3/5);
    texts[TXT_MENU_HIGH_SCORE].set("Ваш максимальный счёт: " + std::to_string(MaxScore), 20, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*3/5+24);
    SDL_SetWindowTitle(app.window, "Астрошутер на SDL");
};

// Pause menu
void pause() {
    // Creating pause text
    Slider MusicSlider(300);
    Slider SoundSlider(450);
    Button BtnFlagUSA(SCREEN_WIDTH/2 - 100, 140, IMG_flag_USA);
    Button BtnFlagRUS(SCREEN_WIDTH/2 + 100, 140, IMG_flag_RUS);

    SDL_Event event;
    bool waiting = true;
    bool MouseDown = false;
    char inBox = NORMAL_BOX;
    Uint64 prevSND = SDL_GetTicks();
    while(waiting) {  // Starting loop for waiting for start
        while( SDL_PollEvent(&event) != 0) {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                running = false;  // Exit from program
                waiting = false;
                break;

            case SDL_EVENT_KEY_DOWN:
                if (event.key.key == SDLK_ESCAPE) {
                    waiting = false;  // Returning to game
                }
                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                MouseDown = true;
                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                MouseDown = false; 
                inBox = NORMAL_BOX;
            }
        }

        float MouseX, MouseY;
        SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position
        if (MouseDown && inBox == NORMAL_BOX) {
            if (MusicSlider.in(MouseX, MouseY)) {
                inBox = MUSIC_SLIDER_BOX;
            }
            else if (SoundSlider.in(MouseX, MouseY)) {
                inBox = EFFECT_SLIDER_BOX;
            }
            else if (BtnFlagUSA.in(MouseX, MouseY)) {
                inBox = ENGLISH_BOX;
            }
            else if (BtnFlagRUS.in(MouseX, MouseY)) {
                inBox = RUSSIAN_BOX;
            }
        }
        switch(inBox)
        {
        case MUSIC_SLIDER_BOX:  // If touch music slider
            MusicVolume = (MouseX - MusicSlider.getX()) / 128;
            if (MouseX - MusicSlider.getX() < 0) MusicVolume = 0;
            if (MouseX - MusicSlider.getX() > 255) MusicVolume = 2.;
            
            //Mix_VolumeMusic(MusicVolume);  // Setting volume of music
            break;
        case EFFECT_SLIDER_BOX:  // If touch effects slider
            EffectsVolume = (MouseX - SoundSlider.getX()) / 128;
            if (MouseX - SoundSlider.getX() < 0) EffectsVolume = 0;
            if (MouseX - SoundSlider.getX() > 255) EffectsVolume = 2.;
            SDL_SetAudioDeviceGain(app.stream, EffectsVolume);
            
            // Playing sound effect for understanding loud
            if ( SDL_GetTicks() - prevSND > 200) {
                Sounds[SND_laser].play();
                prevSND = SDL_GetTicks();
            }
            break;
        case ENGLISH_BOX:  // If touch english language box
            setEnglishText();
            language = ENGLISH_LNG;
            break;
        case RUSSIAN_BOX:  // If touch russian language box
            setRussianText();
            language = RUSSIAN_LNG;
            break;
        }

        // Drawing
        // Drawing background at screen
        SDL_RenderTexture(app.renderer, Textures[IMG_background], NULL, NULL);  
        // Showing extra text
        texts[TXT_PAUSE_PAUSE].draw();
        texts[TXT_PAUSE_MUSIC].draw();
        texts[TXT_PAUSE_SOUND].draw();
        // Drawing sliders
        MusicSlider.blit(MusicVolume*128);
        SoundSlider.blit(EffectsVolume*128);
        // Drawing buttons
        BtnFlagUSA.blit();
        BtnFlagRUS.blit();
        // Drawing advertisment at bottom (if need)
        if (advertisingMode) {
            Advertisment.blit();
        }
        SDL_RenderPresent(app.renderer);  // Blitting textures on screen
        SDL_Delay(1000 / drawFPS);  // Delaying time to decrease CPU loading
    }
};

void startMenu() {
    // Clearing all unnecesary information
    BulletArray.clear();
    PowArray.clear();
    if (MaxScore < score) {  // Updating max score
        MaxScore = score;
    }
    
    if (advertisingMode) {
        //Mix_PlayMusic( Musics[MUS_menu], -1);  // Infinite playing music
    }

    // HUD
    Button esc(SCREEN_WIDTH - 24, 24, IMG_esc_button);
    Animation MenuAdvertisment({96, float(SCREEN_HEIGHT-192), 288, 192}, ANI_menu);

    // Setting text of score, on which language selected
    switch (language)
    {
    case STANDART_LNG:
    case ENGLISH_LNG:
        texts[TXT_MENU_SCORE].set("Your last score: " + std::to_string(score), 20, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*3/5);
        texts[TXT_MENU_HIGH_SCORE].set("Your max score: " + std::to_string(MaxScore), 20, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*3/5+24);
        break;
    
    case RUSSIAN_LNG:
        texts[TXT_MENU_SCORE].set("Ваш последний счёт: " + std::to_string(score), 20, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*3/5);
        texts[TXT_MENU_HIGH_SCORE].set("Ваш максимальный счёт: " + std::to_string(MaxScore), 20, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*3/5+24);
    }

    // Starting loop for waiting for start
    bool waiting = true;
    SDL_Event event;
    while(waiting && running) {
        while( SDL_PollEvent(&event) != 0) {  // Getting events
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                running = false;  // Exit from program
                waiting = false;
                break;
            
            case SDL_EVENT_KEY_DOWN:
                if (event.key.key == SDLK_ESCAPE) {
                    pause();  // Going to pause menu by escape button
                }
                else{
                    waiting = false;
                }
                break;
            
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                float MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position
                if (esc.in(MouseX, MouseY)) {  // Clicking on escape button
                    pause();
                }
            }
        }
        // Drawing
        SDL_RenderTexture(app.renderer, Textures[IMG_background], NULL, NULL);  // Drawing background at screen
        texts[TXT_MENU_SHMUP].draw();
        texts[TXT_MENU_KEYS].draw();
        texts[TXT_MENU_START].draw();
        if (score != 0) {  // Drawing game and max score, if necesary
            texts[TXT_MENU_SCORE].draw();
            texts[TXT_MENU_HIGH_SCORE].draw();
        }

        esc.blit();
        if (advertisingMode) {
            MenuAdvertisment.blit();
        }
        SDL_RenderPresent(app.renderer);

        SDL_Delay( 1000/drawFPS);    // Delaying constant time between ticks to decrease CPU loading
    }
    // Clearing animations
    if (advertisingMode) {
        MenuAdvertisment.clear();
    }

    // Resetting positions and speeds of all objects
    player.reset();
    player.lives = MAX_LIVES; 
    player.shield = MAX_SHIELD;
    MobArray.resize( START_NUM_ASTEROID);
    for(int i=0; i< MobArray.size(); ++i) {
        MobArray[i].reset();
    }

    // Resetting values
    game_over = false;
    score = 0;
    if (advertisingMode) {
        //Mix_PlayMusic( Musics[MUS_main], -1);  // Infinite playing music
    }
}