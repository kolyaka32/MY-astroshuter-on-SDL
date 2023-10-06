#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"
#include "images.hpp"

#include "baseHud.hpp"

// Static text on screen with drawing functions
void staticText::clear(){
    SDL_FreeSurface(Surface);
    SDL_DestroyTexture(Texture);
    TTF_CloseFont(Font);
}

// Creating texture for drawing statick text
void staticText::set(std::string text, int size, ALIGNMENT_types alignment, int x, int y, SDL_Color color ){
    Font = TTF_OpenFont(FONT_NAME, size);  // Reading font to drawing text
    Surface = TTF_RenderUTF8_Solid(Font, text.std::string::c_str(), color);
    Texture = SDL_CreateTextureFromSurface(app.renderer, Surface);
    SDL_QueryTexture(Texture, NULL, NULL, &Rect.w, &Rect.h);
    Rect.x = x - Rect.w * alignment/2; Rect.y = y;
}

// Drawing current statick text at screen
void staticText::draw(){
    SDL_RenderCopy(app.renderer, Texture, NULL, &Rect);
};

// Class of drawing dinamic text at screen
dinamicText::dinamicText(const int size, int x, int y){
    Font = TTF_OpenFont(FONT_NAME, size);  // Reading font to drawing text
    X = x; Rect.y = y;
}
void dinamicText::clear(){
    TTF_CloseFont(Font);
    SDL_FreeSurface(Surface);
    SDL_DestroyTexture(Texture);
}
void dinamicText::draw(std::string text, const ALIGNMENT_types alignment, SDL_Color color){
    Surface = TTF_RenderText_Solid(Font, text.std::string::c_str(), color);
    Texture = SDL_CreateTextureFromSurface(app.renderer, Surface);
    SDL_QueryTexture(Texture, NULL, NULL, &Rect.w, &Rect.h);
    Rect.x = X - Rect.w * alignment/2;
    SDL_RenderCopy(app.renderer, Texture, NULL, &Rect);
};

Slider::Slider(int y){
    textureLine = Textures[IMG_slider_line];
    textureButton = Textures[IMG_slider_button];
    SDL_QueryTexture(textureLine, NULL, NULL, &destLine.w, &destLine.h);
    SDL_QueryTexture(textureButton, NULL, NULL, &destButton.w, &destButton.h);
    destLine.x = SCREEN_WIDTH/2-destLine.w/2; 
    destLine.y = y - destLine.h/2; 
    destButton.y = y - destButton.h/2;
};
void Slider::blit(unsigned char state){
    destButton.x = destLine.x + state - destButton.w/2;
    SDL_RenderCopy(app.renderer, textureLine, NULL, &destLine);
    SDL_RenderCopy(app.renderer, textureButton, NULL, &destButton);
};
bool Slider::in(int x, int y){
    return ((x > destLine.x && x < destLine.x+destLine.w) &&
        (y > destLine.y && y < destLine.y+destLine.h));
}
int Slider::getX(){
    return destLine.x;
}


Button::Button(int x, int y, IMG_names textureIndex){
    texture = Textures[textureIndex];
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    dest.x = x - dest.w/2; 
    dest.y = y - dest.h/2;
};
void Button::blit(){
    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
};
bool Button::in(int x, int y){
    return ((x > dest.x && x < dest.x+dest.w) &&
        (y > dest.y && y < dest.y+dest.h));
};

Animation::Animation( SDL_Rect destination, std::string name ){
    // Creating animation
    SDL_RWops* rwo = SDL_RWFromFile(name.std::string::c_str(), "r");
    anim = IMG_LoadGIFAnimation_RW(rwo);
    SDL_RWclose(rwo);

    dest = destination;
    frame = 0; 
    prevTick = SDL_GetTicks();
};
void Animation::blit(){
    texture = SDL_CreateTextureFromSurface(app.renderer, anim->frames[frame]);
    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
    if(SDL_GetTicks() > prevTick + anim->delays[0]*2/3){
        frame = (frame+1) % anim->count;
        prevTick = SDL_GetTicks();
    }
};
void Animation::clear(){
    SDL_DestroyTexture(texture);
    IMG_FreeAnimation(anim);
};

