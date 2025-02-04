#pragma once

#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

// Text alignment type
enum ALIGNMENT_types{
    LEFT_text,
    MIDLE_text,
    RIGHT_text
};

// Function of creating font with need height
TTF_Font* createFont(float size);

// Static text on screen with drawing functions
class staticText
{
private:
    TTF_Font* font = nullptr;
    SDL_Surface *surface = nullptr;
    SDL_Texture *texture = nullptr;
    SDL_FRect rect = {0, 0, 0, 0};
public:
    void clear();
    void set(const std::string& text, int size, ALIGNMENT_types alignment, int x, int y, SDL_Color color = {255, 255, 255});
    void draw();
};

// Class of drawing dinamic text at screen
class dinamicText
{
private:
    TTF_Font* font = nullptr;
    SDL_Texture *texture = nullptr;
    SDL_FRect rect;
    int x;
public:
    dinamicText(int size, int x, int y);
    void clear();
    void draw(std::string text, ALIGNMENT_types alignment, SDL_Color color = {255, 255, 255});
};

// Class of HUD slider for better choosen parameters
class Slider{
private:
    SDL_Texture *textureLine = nullptr;
    SDL_Texture *textureButton = nullptr;
    SDL_FRect rectLine;
    SDL_FRect rectButton;
public:
    Slider(int y);
    void blit(int state);
    bool in(float x, float y);
    int getX();
};

class Button
{
private:
    SDL_Texture *texture;
    SDL_FRect rect;
public:
    Button(int x, int y, IMG_names textureIndex);
    void blit();
    bool in(float x, float y);
};

class Animation
{
private:
    const Uint8 type;
    SDL_Texture* texture = nullptr;
    Uint32 frame;
    Uint64 prevTick;
    const SDL_FRect dest;
public:
    Animation(SDL_FRect destination, ANI_names newType);
    void blit();
    void clear();
};

class Bar
{
private:
    SDL_FRect rectBack;
    SDL_FRect rectFront;
    const SDL_FRect iconeRect;
    SDL_Texture* iconeTexture = nullptr;
    const SDL_Color color;
public:
    Bar(const SDL_FRect dest, SDL_Color color, IMG_names icone);
    void blit(int width);
};
