#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

#include "pause.hpp"

enum{  // Types of selected box
    NORMAL_BOX,
    MUSIC_SLIDER_BOX,
    EFFECT_SLIDER_BOX,
    ENGLISH_BOX,
    RUSSIAN_BOX,
} SELCTED_BOX_types;

void setEnglishText(){
    TXT_SHMUP.set("SHMUP!", 64, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT/5);
    TXT_KEYS.set("Arrow keys move, Space to fire", 22, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*2/5);
    TXT_START.set("Press any key to begin", 18, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*2/5+70);
    TXT_Pause.set("Game on pause", 30, MIDLE_text, SCREEN_WIDTH/2, 20);
    TXT_Music.set("Music", 22, MIDLE_text, SCREEN_WIDTH/2, 250);
    TXT_Sound.set("Sounds", 22, MIDLE_text, SCREEN_WIDTH/2, 400);
    MenuHighScore.set("Your last score: " + std::to_string(score), 20, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*3/5);
    MenuMaxScore.set("Your max score: " + std::to_string(MaxScore), 20, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*3/5+24);
    SDL_SetWindowTitle(app.window, "Astroshuter on SDL");
};

void setRussianText(){
    TXT_SHMUP.set("ШМАП!", 64, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT/5);
    TXT_KEYS.set("Стрелки для движения, пробел для стрельбы", 22, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*2/5);
    TXT_START.set("Нажмите любую кнопку для продолжения", 18, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*2/5+70);
    TXT_Pause.set("Игра на паузе", 30, MIDLE_text, SCREEN_WIDTH/2, 20);
    TXT_Music.set("Музыка", 22, MIDLE_text, SCREEN_WIDTH/2, 250);
    TXT_Sound.set("Звук", 22, MIDLE_text, SCREEN_WIDTH/2, 400);
    MenuHighScore.set("Ваш последний счёт: " + std::to_string(score), 20, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*3/5);
    MenuMaxScore.set("Ваш максимальный счёт: " + std::to_string(MaxScore), 20, MIDLE_text, SCREEN_WIDTH/2, GAME_HEIGHT*3/5+24);
    SDL_SetWindowTitle(app.window, "Астрошутер на SDL");
};

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
    char inBox = NORMAL_BOX;
    while(waiting){  // Starting loop for waiting for start
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;  // Exit from program
                waiting = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    waiting = false;  // Returning to game
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                MouseDown = true;
                break;

            case SDL_MOUSEBUTTONUP:
                MouseDown = false; 
                inBox = NORMAL_BOX;
            }
        }

        int MouseX, MouseY;
        SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position
        if(MouseDown && inBox == NORMAL_BOX){
            if(MusicSlider.in(MouseX, MouseY)){
                inBox = MUSIC_SLIDER_BOX;
            }
            else if(SoundSlider.in(MouseX, MouseY)){
                inBox = EFFECT_SLIDER_BOX;
            }
            else if(BtnFlagUSA.in(MouseX, MouseY)){
                inBox = ENGLISH_BOX;
            }
            else if(BtnFlagRUS.in(MouseX, MouseY)){
                inBox = RUSSIAN_BOX;
            }
        }
        switch(inBox)
        {
        case MUSIC_SLIDER_BOX:  // If touch music slider
            MusicVolume = (MouseX - MusicSlider.getX()) / 2;
            if(MouseX - MusicSlider.getX() < 0) MusicVolume = 0;
            if(MouseX - MusicSlider.getX() > 255) MusicVolume = 255;
            Mix_VolumeMusic(MusicVolume);  // Setting volume of music
            break;
        case EFFECT_SLIDER_BOX:  // If touch effects slider
            EffectsVolume = (MouseX - SoundSlider.getX()) / 2;
            if(MouseX - SoundSlider.getX() < 0) EffectsVolume = 0;
            if(MouseX - SoundSlider.getX() > 255) EffectsVolume = 255;
            Mix_Volume(-1, EffectsVolume);  // Setting volume of effects
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
        SDL_RenderCopy(app.renderer, Textures[IMG_background], NULL, NULL);  // Drawing background at screen
        TXT_Pause.draw();  TXT_Music.draw(); TXT_Sound.draw();  // Showing extra text
        MusicSlider.blit(MusicVolume*2);
        SoundSlider.blit(EffectsVolume*2);  // Drawing sliders
        BtnFlagUSA.blit();
        BtnFlagRUS.blit();  // Drawing buttons
        #if ADVERTISMENT_MOD
            Advertisment.blit();  // Drawing advertisment at bottom
        #endif
        SDL_RenderPresent(app.renderer);  // Blitting textures on screen
        SDL_Delay(1000 / FPS);  // Delaying time to decrease CPU loading
    }
};
