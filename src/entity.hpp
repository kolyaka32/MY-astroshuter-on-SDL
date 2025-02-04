#pragma once

#include "include.hpp"

// Game classes
// Base entity in-game class
class Entity{
protected:
    int speedx, speedy;    // Speeds (or deltas) - movement per tick
    SDL_Texture *texture;  // Poiter to texture of sprite
public:
    SDL_FRect dest;         // Base destination of drawing
    virtual void blit();    // Base drawing function
    virtual void update();  // Base update and moving function
};


// Main head (player) class
class Head : public Entity {
    Uint8 frame;            // Frame counter of animation
    Uint8 lastShootTicks;   // Ticks from last shoot
    int dx;                 // Delta speed for movement
public:
    Uint8 shield;           // "Health bar"
    Uint8 lives;            // Counter of rest lives

    void reset();           // Function of resseting poition and texture
    void moveLeft();        // Try move left
    void moveRight();       // Try move right
    void stop();            // Try stopping movement
    void tryShoot();        // Try shoot bullet
    void update() override; // Update position and animation frame
    void blitLives();       // Function of drawing lives at screen
    void setAnimation();    // Set explosion animation
    bool isAnimation();     // Checking if the animation in progress
};


// Bullet class
class Bullet:public Entity {
public:
    Bullet(int PosX, int PosY);  // Setting new bullet at need position
    bool isOver();               // Checking if get over screen
};


// Mob (asteroid) class
class Mob : public Entity {
private:
    float rot, dRot;      // Rotation state and speed of it changing
    Uint8 frame;          // Frame counter of animation
public:
    void reset();         // Spawning new asteroid with unique charachteristicks
    void update() override;  // Update position and animation frame
    bool isOver();        // Checking if get over screen
    void blit() override; // Function of drawing at screen
    void setAnimation();  // Set explosion animation
    bool isAnimation();   // Checking if the animation in progress
};


// Power-up (boosters) class
class Pow:public Entity {
private:
    Uint8 type;              // Type of current powerup (from POW_types)
public:
    Pow(SDL_FRect position);  // Spawning new powerup, base on position
    void activate();         // Activate ability of current powerup
    bool isOver();           // Checking if get over screen
};
