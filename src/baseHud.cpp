#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"
#include "images.hpp"

#include "baseHud.hpp"

//SDL_Texture *Textures[IMG_count];  // Array of all textures
//App app;

// Static text on screen with drawing functions
staticText::~staticText(){
    SDL_FreeSurface(Surface);
    SDL_DestroyTexture(Texture);
    TTF_CloseFont(Font);
}

void staticText::set(std::string text, int size, SDL_Color color, int x, int y){
    Font = TTF_OpenFont("Arial.ttf", size);  // Reading font to drawing text
    Surface = TTF_RenderUTF8_Solid(Font, text.std::string::c_str(), color);
    Texture = SDL_CreateTextureFromSurface(app.renderer, Surface);
    SDL_QueryTexture(Texture, NULL, NULL, &Rect.w, &Rect.h);
    Rect.x = x - Rect.w/2; Rect.y = y;
}

void staticText::draw(){
    SDL_RenderCopy(app.renderer, Texture, NULL, &Rect);
};

// Class of drawing dinamic text at screen
dinamicText::dinamicText(int size, int x, int y){
    Font = TTF_OpenFont("Arial.ttf", size);  // Reading font to drawing text
    Rect.x = x; Rect.y = y;
}
dinamicText::~dinamicText(){
    SDL_FreeSurface(Surface);
    SDL_DestroyTexture(Texture);
    TTF_CloseFont(Font);
}
void dinamicText::draw(std::string text, SDL_Color color){
    Surface = TTF_RenderText_Solid(Font, text.std::string::c_str(), color);
    Texture = SDL_CreateTextureFromSurface(app.renderer, Surface);
    SDL_QueryTexture(Texture, NULL, NULL, &Rect.w, &Rect.h);
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
}
