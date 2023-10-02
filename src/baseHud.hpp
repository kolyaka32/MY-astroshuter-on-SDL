#pragma once

#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

// Static text on screen with drawing functions
class staticText
{
private:
    TTF_Font* Font;
    SDL_Surface *Surface;
    SDL_Texture *Texture;
    SDL_Rect Rect;
public:
    ~staticText();
    void set(std::string text, int size, SDL_Color color, int x, int y);
    void draw();
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
    dinamicText(int size, int x, int y);
    ~dinamicText();
    void draw(std::string text, SDL_Color color);
};

class Slider{
private:
    SDL_Texture *textureLine;
    SDL_Texture *textureButton;
    SDL_Rect destLine;
    SDL_Rect destButton;
public:
    Slider(int y);
    void blit(unsigned char state);
    bool in(int x, int y);
    int getX();
};

class Button
{
private:
    SDL_Texture *texture;
    SDL_Rect dest;
public:
    Button(int x, int y, IMG_names textureIndex);
    void blit();
    bool in(int x, int y);
};
