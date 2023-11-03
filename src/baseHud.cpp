#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"
#include "dataLoader.hpp"
#include "baseHud.hpp"

// Function of creating font
TTF_Font* createFont(int size){
    SDL_RWops* tempRW = SDL_RWFromMem(fontData.fontMem, fontData.size);
    return TTF_OpenFontRW(tempRW, 1, size);
};

// Class of static text
void staticText::clear(){
    SDL_FreeSurface(Surface);
    SDL_DestroyTexture(Texture);
    TTF_CloseFont(Font);
};

void staticText::set(std::string text, int size, ALIGNMENT_types alignment, int x, int y, SDL_Color color ){
    Font = createFont(size);
    Surface = TTF_RenderUTF8_Solid(Font, text.std::string::c_str(), color);
    Texture = SDL_CreateTextureFromSurface(app.renderer, Surface);
    SDL_QueryTexture(Texture, NULL, NULL, &Rect.w, &Rect.h);
    Rect.x = x - Rect.w * alignment/2; Rect.y = y;
};

void staticText::draw(){
    SDL_RenderCopy(app.renderer, Texture, NULL, &Rect);
};


// Class of drawing dinamic text at screen
dinamicText::dinamicText(const int size, int x, int y){
    Font = createFont(size);
    X = x; Rect.y = y;
}

void dinamicText::clear(){
    TTF_CloseFont(Font);
    //SDL_FreeSurface(Surface);
    SDL_DestroyTexture(Texture);
}

void dinamicText::draw(std::string text, const ALIGNMENT_types alignment, SDL_Color color){
    Surface = TTF_RenderText_Solid(Font, text.std::string::c_str(), color);
    Texture = SDL_CreateTextureFromSurface(app.renderer, Surface);
    SDL_QueryTexture(Texture, NULL, NULL, &Rect.w, &Rect.h);
    Rect.x = X - Rect.w * alignment/2;
    SDL_RenderCopy(app.renderer, Texture, NULL, &Rect);
};

// Slider class
Slider::Slider(int y){
    textureLine = Textures[IMG_slider_line];
    textureButton = Textures[IMG_slider_button];
    SDL_QueryTexture(textureLine, NULL, NULL, &destLine.w, &destLine.h);
    SDL_QueryTexture(textureButton, NULL, NULL, &destButton.w, &destButton.h);
    destLine.x = SCREEN_WIDTH/2-destLine.w/2; 
    destLine.y = y - destLine.h/2; 
    destButton.y = y - destButton.h/2;
};

void Slider::blit(Uint8 state){
    destButton.x = destLine.x + state - destButton.w/2;
    SDL_RenderCopy(app.renderer, textureLine, NULL, &destLine);
    SDL_RenderCopy(app.renderer, textureButton, NULL, &destButton);
};

bool Slider::in(int x, int y){
    return ((x > destLine.x && x < destLine.x+destLine.w) &&
        (y > destLine.y && y < destLine.y+destLine.h));
};

int Slider::getX(){
    return destLine.x;
};

// Button class
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


// GIF animation play
Animation::Animation( SDL_Rect destination, ANIM_types newType ){
    // Creating animation
    type = newType;
    dest = destination;
    frame = 0; 
    prevTick = 0;
};

void Animation::blit(){
    texture = SDL_CreateTextureFromSurface(app.renderer, Animations[type]->frames[frame]);
    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
    if(SDL_GetTicks64() > prevTick + Animations[type]->delays[0]*2/3){
        frame = (frame+1) % Animations[type]->count;
        prevTick = SDL_GetTicks64();
    }
};

void Animation::clear(){
    SDL_DestroyTexture(texture);
};


// Bar class
Bar::Bar( const SDL_Rect dest, SDL_Color newColor, IMG_names icone ){
    // Base bar
    Back_rect = dest;
    Front_rect = dest;
    color = newColor;
    // Icone part
    IconeTexture = Textures[icone];  // Texture of icone

    IconeRect = dest;
    IconeRect.w = 14;
    IconeRect.h = 16;
    IconeRect.y -= 2;
    IconeRect.x -= IconeRect.w+2;
};

void Bar::blit( int width ){
    Front_rect.w = width;  // Setting width (health bar) 
    SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);  // Drawing back part
    SDL_RenderFillRect(app.renderer, &Back_rect);  
    SDL_SetRenderDrawColor(app.renderer, color.r, color.g, color.b, color.a);  // Drawing front part
    SDL_RenderFillRect(app.renderer, &Front_rect);
    SDL_RenderCopy(app.renderer, IconeTexture, NULL, &IconeRect);  // Rendering icone
};

