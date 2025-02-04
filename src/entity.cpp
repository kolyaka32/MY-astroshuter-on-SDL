#include "include.hpp"
#include "structs.hpp"
#include "dataLoader.hpp"

// Base entity class
// Base destination of drawing
void Entity::blit() {
    SDL_RenderTexture(app.renderer, texture, NULL, &dest); 
};

// Base update and moving function
void Entity::update() {
    dest.x += speedx; 
    dest.y += speedy;
};


// Head class
// Function of resseting poition and texture
void Head::reset() {
    // Resetting texture
    texture = Textures[IMG_player];
    SDL_GetTextureSize(texture, &dest.w, &dest.h);
    dest.h /= 2; 
    dest.w /= 2;
    speedx = 0; 
    speedy = 0;
    // Setting up standart position
    dest.x = SCREEN_WIDTH/2 - dest.w/2;  
    dest.y = GAME_HEIGHT - 80;
    frame = 0;
    // Resseting ticks
    lastShootTicks = 0;
    lastBoostTicks = 0;
};

// Try move left
void Head::moveLeft() {
    if (dx > -MOVE_SPEED) dx -= MOVE_SPEED;
};

// Try move right
void Head::moveRight() {
    if (dx < MOVE_SPEED) dx += MOVE_SPEED;
};

// Try stopping movement
void Head::stop() {
    dx = 0;
};

// Try shoot bullet
void Head::tryShoot() {
    if (isAnimation() && (lastShootTicks >= D_SHOOT_TICKS)) {
        lastShootTicks = 0;
        if (lastBoostTicks > 0) {  // Creating double shoot 
            Bullet newBullet1(dest.x, dest.y-20);
            Bullet newBullet2(dest.x + dest.w-12, dest.y-20);
            BulletArray.push_back(newBullet1);
            BulletArray.push_back(newBullet2);
        }
        else{  // Creating normal shoot
            Bullet newBullet(dest.x + dest.w/2-6, dest.y-20);
            BulletArray.push_back(newBullet);
        }
        Sounds[SND_laser].play();  // Playing sound of shooting
    }
};

// Update position and animation frame
void Head::update() {
    if (frame != 0) {  
        // Playing animation of explosion
        frame += 1;
        if (frame % 5 == 0) {
            dest.x += dest.h/2; 
            dest.y += dest.w/2;
            texture = Textures[frame/5];
            SDL_GetTextureSize(texture, &dest.w, &dest.h);
            dest.w/=2; dest.h/=2;
            dest.x -= dest.h/2; dest.y -= dest.w/2;
        }
        if (frame/5 >= IMG_sonic_explosion7) {
            // Exiting animation
            shield = MAX_SHIELD;
            lives -= 1;
            if (lives == 0) {
                game_over = true;
            }
            reset();
        }
    } else {  
        // Normal movement
        dest.x += dx;
        if (dest.x + dest.w > SCREEN_WIDTH) {
            dest.x=SCREEN_WIDTH-dest.w;
            dx = 0;
        }
        if (dest.x < 0) {
            dest.x=0;
            dx = 0;
        }
        if (lastShootTicks < D_SHOOT_TICKS) {  // Adding tick to counter
            lastShootTicks++;
        }
    }
};

// Function of drawing lives at screen
void Head::blitLives() {
    for(int i=0; i < lives; ++i) {
        SDL_FRect dest = { (float)(SCREEN_WIDTH-160+40*i), 5., 36., 27.};
        SDL_RenderTexture(app.renderer, Textures[IMG_player], NULL, &dest); 
    }
};

// Set explosion animation
void Head::setAnimation() {
    frame = IMG_sonic_explosion0*5;
    texture = Textures[ frame/5 ];
    SDL_GetTextureSize(texture, &dest.w, &dest.h);
    dest.w /= 2; dest.h /= 2;
}

// Checking if the animation in progress
bool Head::isAnimation() {
    return (frame == 0);
};


// Bullet class
// Setting new bullet at need position
Bullet::Bullet(int PosX, int PosY) {
    speedx = 0; speedy = -LASER_SPEED;
    dest.x = PosX; dest.y = PosY;
    texture = Textures[IMG_laser];
    SDL_GetTextureSize(texture, &dest.w, &dest.h);
};

// Checking if get over screen
bool Bullet::isOver() {
    return dest.y < 0;
};


// Mob class
// Spawning new asteroid with unique charachteristicks
void Mob::reset() {
    texture = Textures[IMG_meteor0 + rand() % METEOR_COUNT];
    speedx = rand() % 6 - 3;
    speedy = rand() % 7 + 1;
    SDL_GetTextureSize(texture, &dest.w, &dest.h);
    dest.y = -dest.h - rand() % 80;
    dest.x = rand() % (SCREEN_WIDTH - (int)dest.w);
    rot = (rand() % 20)/10;
    dRot = (float)(rand() % 16)/10 - 8;
    frame = 0;
};

// Update position and animation frame
void Mob::update() {
    if (frame != 0) {
        frame += 1;
        if (frame % 4 == 0) {
            dest.x += dest.h/2;
            dest.y += dest.w/2;
            texture = Textures[frame/4];
            SDL_GetTextureSize(texture, &dest.w, &dest.h);
            dest.w/=2;
            dest.h/=2;
            dest.x -= dest.h/2;
            dest.y -= dest.w/2;
        }
        if (frame/4 == IMG_regular_explosion8) {
            reset();
        }
    }
    else{
        dest.x += speedx;
        dest.y += speedy;
        rot += dRot;
    }
};

// Checking if get over screen
bool Mob::isOver() {
    return (dest.y - dest.h > GAME_HEIGHT) || (dest.x > SCREEN_WIDTH) || (dest.x+dest.w < 0);
};

// Function of drawing at screen
void Mob::blit() {
    SDL_RenderTextureRotated( app.renderer, texture, NULL, &dest, rot, NULL, SDL_FLIP_NONE );
};

// Set explosion animation
void Mob::setAnimation() {
    rot = 0;
    frame = IMG_regular_explosion0*4;
    texture = Textures[frame/4];
    SDL_GetTextureSize(texture, &dest.w, &dest.h);
    dest.w/=2;
    dest.h/=2;
};

// Checking if the animation in progress
bool Mob::isAnimation() {
    return (frame == 0);
};


// Powerup class
// Spawning new powerup, base on position
Pow::Pow(SDL_FRect position) {
    speedx = 0;
    speedy = 2;
    dest = position; 
    dest.x += dest.w/2;
    dest.y += dest.h/2;
    type = rand() % POW_count;
    texture = Textures[IMG_bolt + type];
    SDL_GetTextureSize(texture, &dest.w, &dest.h);
    dest.x -= dest.w/2;
    dest.y -= dest.h/2;
};

// Activate ability of current powerup
void Pow::activate() {
    switch (type)
    {
    case POW_bolt:
        lastBoostTicks = D_POWERUP_TICKS;  // Setting ticks for boost
        Sounds[SND_bolt].play();
        break;
    
    case POW_shield:
        player.shield += rand() % 20 + 10;
        if (player.shield >= MAX_SHIELD) {
            player.shield = MAX_SHIELD;
        }
        Sounds[SND_shield].play();
        break;

    }
};

// Checking if get over screen
bool Pow::isOver() {
    return dest.y > GAME_HEIGHT;
};
