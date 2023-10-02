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

    Entity(){};
    ~Entity(){};
    void init();
    void blit();
    void update();
};

class Head:public Entity
{
public:
    unsigned char frame;
    unsigned char shield;
    unsigned char lives;
    //SDL_Rect dest;  // Rectangle for collisions
    int speedx, speedy;  // Delta speed for movement

    void init();
    void blit();
    void reset();
    void update();
    void setAnimation();
    bool isAnimation();
    void shoot();
};

class Bullet:public Entity
{
public:
    //SDL_Rect dest;  // Rectangle for collisions

    Bullet(int PosX, int PosY);
    
    bool isOver();
};

class Mob:public Entity
{
private:
    int rot; int dRot;
    unsigned char frame;
public:
    //SDL_Rect dest;  // Rectangle for collisions

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
    //SDL_Rect dest;  // Rectangle for collisions

    Pow(SDL_Rect position);
    void activate();
    bool isOver();
};
