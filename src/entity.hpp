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


// Main head (player) class
class Head:public Entity
{
    Uint8 frame;
    Uint8 lastShootTicks;  // Ticks from last shoot
    int dx;  // Delta speed for movement
public:
    Uint8 shield;
    Uint8 lives;

    void reset();
    void blit();
    void blitLives();
    void moveLeft();
    void moveRight();
    void stop();
    void update();
    void tryShoot();
    void setAnimation();
    bool isAnimation();
};


// Bullet class
class Bullet:public Entity
{
public:
    Bullet(int PosX, int PosY);
    bool isOver();
};


// Mob (asteroid) class
class Mob:public Entity
{
private:
    float rot; float dRot;
    Uint8 frame;
    bool original;
public:
    Mob();
    void blit();
    void update();
    void reset();
    void setAnimation();
    bool isOver();
    bool isAnimation();
    SDL_Rect getDest();
};


// Power-up (boosters) class
class Pow:public Entity
{
private:
    char type;
public:
    Pow(SDL_Rect position);
    void activate();
    bool isOver();
};
