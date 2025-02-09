/*
 * Copyright (C) 2024-2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"
#include "dataLoader.hpp"
#include "baseHud.hpp"

// Function of creating font
TTF_Font* createFont(float size) {
    SDL_IOStream* tempRW = SDL_IOFromConstMem(fontMemory, fontSize);
    return TTF_OpenFontIO(tempRW, true, size);
}

// Class of static text
void staticText::clear() {
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

void staticText::set(const std::string& text, int size, ALIGNMENT_types alignment, int x, int y, SDL_Color color) {
    font = createFont(size);
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.std::string::c_str(), text.size(), color);
    texture = SDL_CreateTextureFromSurface(app.renderer, surface);
    SDL_DestroySurface(surface);
    SDL_GetTextureSize(texture, &rect.w, &rect.h);
    rect.x = x - rect.w * alignment/2;
    rect.y = y;
}

void staticText::draw() {
    SDL_RenderTexture(app.renderer, texture, NULL, &rect);
}


// Class of drawing dinamic text at screen
dinamicText::dinamicText(int size, int _x, int _y) {
    font = createFont(size);
    x = _x;
    rect.y = _y;
}

void dinamicText::clear() {
    TTF_CloseFont(font);
    SDL_DestroyTexture(texture);
}

void dinamicText::draw(const std::string& _text, ALIGNMENT_types alignment, SDL_Color color) {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    SDL_Surface* surface = TTF_RenderText_Solid(font, _text.std::string::c_str(), _text.size(), color);
    texture = SDL_CreateTextureFromSurface(app.renderer, surface);
    SDL_DestroySurface(surface);
    SDL_GetTextureSize(texture, &rect.w, &rect.h);
    rect.x = x - rect.w * alignment/2;
    SDL_RenderTexture(app.renderer, texture, NULL, &rect);
}

// Slider class
Slider::Slider(int y) {
    textureLine = Textures[IMG_slider_line];
    textureButton = Textures[IMG_slider_button];
    SDL_GetTextureSize(textureLine, &rectLine.w, &rectLine.h);
    SDL_GetTextureSize(textureButton, &rectButton.w, &rectButton.h);
    rectLine.x = SCREEN_WIDTH/2-rectLine.w/2; 
    rectLine.y = y - rectLine.h/2; 
    rectButton.y = y - rectButton.h/2;
}

void Slider::blit(int state) {
    rectButton.x = rectLine.x + state - rectButton.w/2;
    SDL_RenderTexture(app.renderer, textureLine, NULL, &rectLine);
    SDL_RenderTexture(app.renderer, textureButton, NULL, &rectButton);
}

bool Slider::in(float x, float y) {
    return ((x > rectLine.x && x < rectLine.x + rectLine.w) &&
        (y > rectLine.y && y < rectLine.y + rectLine.h));
}

int Slider::getX() {
    return rectLine.x;
}

// Button class
Button::Button(int x, int y, IMG_names textureIndex) {
    texture = Textures[textureIndex];
    SDL_GetTextureSize(texture, &rect.w, &rect.h);
    rect.x = x - rect.w/2; 
    rect.y = y - rect.h/2;
}

void Button::blit() {
    SDL_RenderTexture(app.renderer, texture, NULL, &rect);
}

bool Button::in(float x, float y) {
    return ((x > rect.x && x < rect.x + rect.w) &&
        (y > rect.y && y < rect.y + rect.h));
}


// GIF animation play
Animation::Animation( SDL_FRect _dest, ANI_names _type)
: dest(_dest), type(_type) {
    // Resetting frames
    frame = 0;
    prevTick = 0;
}

void Animation::blit() {
    if (SDL_GetTicks() > prevTick) {
        frame = (frame + 1) % Animations[type]->count;
        SDL_DestroyTexture(texture);
        texture = SDL_CreateTextureFromSurface(app.renderer, Animations[type]->frames[frame]);
        prevTick = SDL_GetTicks() + Animations[type]->delays[frame] / 2;
    }
    SDL_RenderTexture(app.renderer, texture, NULL, &dest);
}

void Animation::clear() {
    SDL_DestroyTexture(texture);
}


// Bar class
Bar::Bar(const SDL_FRect _dest, SDL_Color _color, IMG_names icone)
: iconeRect({_dest.x - 16, _dest.y - 2, 14, 16}),
iconeTexture(Textures[icone]),
rectBack(_dest),
rectFront(_dest),
color(_color) {}

void Bar::blit(int width) {
    rectFront.w = width;  // Setting width (health bar) 
    SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);  // Drawing back part
    SDL_RenderFillRect(app.renderer, &rectBack);  
    SDL_SetRenderDrawColor(app.renderer, color.r, color.g, color.b, color.a);  // Drawing front part
    SDL_RenderFillRect(app.renderer, &rectFront);
    SDL_RenderTexture(app.renderer, iconeTexture, NULL, &iconeRect);  // Rendering icone
}
