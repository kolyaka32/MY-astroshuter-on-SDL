#pragma once

#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

// Game classes
// Base entity in-game class
class Entity{
protected:
    int speedx, speedy;
    SDL_Texture *texture;
public:
    SDL_Rect dest;

    void blit();
    void update();
};

class Head:public Entity
{
    unsigned char frame;
public:
    unsigned char shield;
    unsigned char lives;
    int speedx;  // Delta speed for movement

    void reset();
    void blit();
    void blitLives();
    void update();
    void shoot();
    void setAnimation();
    bool isAnimation();
};

class Bullet:public Entity
{
public:
    Bullet(int PosX, int PosY);
    bool isOver();
};

class Mob:public Entity
{
private:
    int rot; int dRot;
    unsigned char frame;
public:
    void init();
    void blit();
    void update();
    void reset();
    void setAnimation();
    bool isOver();
    bool isAnimation();
    SDL_Rect getDest();
};

class Pow:public Entity
{
private:
    char type;
public:
    Pow(SDL_Rect position);
    void activate();
    bool isOver();
};
