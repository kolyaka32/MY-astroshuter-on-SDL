#include "include.hpp"
#include "structs.hpp"

#include "images.hpp"

int c;  // Counter of loaded textures

// Load all textures
bool loadAllTextures(){
    c = 0;  // Loading textures with they names

    // Base hud elements
    loadTexture(IMG_background, "img/starfield.png");
    loadTexture(IMG_esc_button, "img/esc_button.png");
    loadTexture(IMG_slider_line, "img/slider_line.png");
    loadTexture(IMG_slider_button, "img/slider_button.png");
    loadTexture(IMG_flag_USA, "img/Flag_USA.png");
    loadTexture(IMG_flag_RUS, "img/Flag_RUS.png");
    loadTexture(IMG_player, "img/playerShip1_orange.png");
    loadTexture(IMG_laser, "img/laserRed16.png");

    // Meteors types
    loadTexture(IMG_meteor0, "img/meteorBrown_big1.png");
    loadTexture(IMG_meteor1, "img/meteorBrown_med1.png");
    loadTexture(IMG_meteor2, "img/meteorBrown_med3.png");
    loadTexture(IMG_meteor3, "img/meteorBrown_small1.png");
    loadTexture(IMG_meteor4, "img/meteorBrown_small2.png");
    loadTexture(IMG_meteor5, "img/meteorBrown_tiny1.png");
    
    #if MEME_MOD  // Extra mem edition
        loadTexture(IMG_meteorSpecial, "img/raian-gosling-25.png");
    #endif

    // Powerups
    loadTexture(IMG_bolt, "img/bolt_gold.png");
    loadTexture(IMG_shield, "img/shield_gold.png");

    // Meteor explosion animation
    loadTexture(IMG_regular_explosion0, "img/regularExplosion00.png");
    loadTexture(IMG_regular_explosion1, "img/regularExplosion01.png");
    loadTexture(IMG_regular_explosion2, "img/regularExplosion02.png");
    loadTexture(IMG_regular_explosion3, "img/regularExplosion03.png");
    loadTexture(IMG_regular_explosion4, "img/regularExplosion04.png");
    loadTexture(IMG_regular_explosion5, "img/regularExplosion05.png");
    loadTexture(IMG_regular_explosion6, "img/regularExplosion06.png");
    loadTexture(IMG_regular_explosion7, "img/regularExplosion07.png");
    loadTexture(IMG_regular_explosion8, "img/regularExplosion08.png");

    // Player explosion animation
    loadTexture(IMG_sonic_explosion0, "img/sonicExplosion00.png");
    loadTexture(IMG_sonic_explosion1, "img/sonicExplosion01.png");
    loadTexture(IMG_sonic_explosion2, "img/sonicExplosion02.png");
    loadTexture(IMG_sonic_explosion3, "img/sonicExplosion03.png");
    loadTexture(IMG_sonic_explosion4, "img/sonicExplosion04.png");
    loadTexture(IMG_sonic_explosion5, "img/sonicExplosion05.png");
    loadTexture(IMG_sonic_explosion6, "img/sonicExplosion06.png");
    loadTexture(IMG_sonic_explosion7, "img/sonicExplosion07.png");

    return (c == IMG_count);  // Returning correcting of loading
}

void loadTexture(IMG_names number, std::string name){
    SDL_Texture *temp_texture = IMG_LoadTexture(app.renderer, (name).std::string::c_str() );
    if(temp_texture != NULL){
        Textures[number] = temp_texture;
        c+=1;
    }
}

// Function of clearing data 
void unloadTextures(){
    for(int i = 0; i < IMG_count; ++i){
        SDL_DestroyTexture(Textures[i]);
        Textures[i] = NULL;
    }
}
