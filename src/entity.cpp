
#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

#include "images.hpp"

#include "entity.hpp"

// Base entity class
void Entity::blit(){
    SDL_RenderCopy(app.renderer, texture, NULL, &dest); 
};
void Entity::update(){
    dest.x += speedx; dest.y += speedy;
};

// Head class
void Head::blit(){
    SDL_RenderCopy(app.renderer, texture, NULL, &dest); 
};
void Head::blitLives(){
    for(int i=0; i < lives; ++i){
            SDL_Rect dest = { SCREEN_WIDTH-160+40*i, 5, 36, 27};
	        SDL_RenderCopy(app.renderer, Textures[IMG_player], NULL, &dest); 
        }
}
void Head::reset(){
    texture = Textures[IMG_player];
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    dest.h /= 2; dest.w /= 2;
    //speedx = 0; speedy = 0;
    dest.x = SCREEN_WIDTH/2 - dest.w/2;
    dest.y = GAME_HEIGHT - 80;
    frame = 0;
    oldShootTime = SDL_GetTicks();
    BoostTime = -POWERUP_TIME;
};
void Head::moveLeft(){
    if(ddx >= -1) ddx -= 1;
};
void Head::moveRight(){
    if(ddx <= 1) ddx += 1;
};
void Head::stop(){
    ddx = 0;
};
void Head::update(){
    if(frame != 0){  // Playing animation of explosion
        frame += 1;
        if(frame % 5 == 0){
            dest.x += dest.h/2; dest.y += dest.w/2;
            texture = Textures[frame/5];
            SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
            dest.w/=2; dest.h/=2;
            dest.x -= dest.h/2; dest.y -= dest.w/2;
        }
        if(frame/5 >= IMG_sonic_explosion7){
            shield = MAX_SHIELD;
            lives -= 1;
            if(lives <= 0){
                game_over = true;
            }
            reset();

        }
    }
    else{  // Normal movement
        if(ddx == 0) dx/=2;
        else dx += ddx;
        dest.x += dx;
        if(dest.x + dest.w > SCREEN_WIDTH){
            dest.x=SCREEN_WIDTH-dest.w;
            dx = 0;
        }
        if(dest.x < 0){
            dest.x=0;
            dx = 0;
        }
    }
}
void Head::setAnimation(){
    frame = IMG_sonic_explosion0*5;
    texture = Textures[ frame/5 ];
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    dest.w/=2; dest.h/=2;
}
bool Head::isAnimation(){
    return (frame == 0);
}
void Head::shoot(){
    if(SDL_GetTicks() - oldShootTime > SHOOT_TIME){
        oldShootTime = SDL_GetTicks();
        if(SDL_GetTicks() - BoostTime < POWERUP_TIME){  // Creating double shoot 
            Bullet newBullet1(dest.x, dest.y-20);
            Bullet newBullet2(dest.x + dest.w-12, dest.y-20);
            BulletArray.push_back(newBullet1);
            BulletArray.push_back(newBullet2);
        }
        else{  // Creating normal shoot
                Bullet newBullet(dest.x + dest.w/2-6, dest.y-20);
            BulletArray.push_back(newBullet);
        }
        Mix_PlayChannel(-1, Sounds[SND_laser], 0);  // Playing sound of shooting
    }
}

// Bullet class
Bullet::Bullet(int PosX, int PosY){  //Spawning 
    speedx = 0; speedy = -LASER_SPEED;
    dest.x = PosX; dest.y = PosY;
    texture = Textures[IMG_laser];
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
}
bool Bullet::isOver(){
    return dest.y < 0;
}

// Mob class
Mob::Mob(){
    texture = Textures[IMG_meteor0];
    frame = 0;
};
void Mob::blit(){
    SDL_RenderCopyEx( app.renderer, texture, NULL, &dest, rot, NULL, SDL_FLIP_NONE );
}
void Mob::update(){
    if(frame != 0){
        frame += 1;
        if(frame % 4 == 0){
            dest.x += dest.h/2; dest.y += dest.w/2;
            texture = Textures[frame/4];
            SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
            dest.w/=2; dest.h/=2;
            dest.x -= dest.h/2; dest.y -= dest.w/2;
        }
        if(frame/4 == IMG_regular_explosion8){
            reset();
        }
    }
    else{
        dest.x += speedx; dest.y += speedy; rot += dRot;
    }
};
void Mob::reset(){
    texture = Textures[IMG_meteor0 + rand() % METEOR_COUNT];
    speedx = rand() % 6 - 3;
    speedy = rand() % 7 + 1;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    dest.y = -dest.h - rand() % 80;
    dest.x = rand() % (SCREEN_WIDTH - dest.w);
    dRot = rand() % 16 - 8;
    frame = 0;
}
void Mob::setAnimation(){
    rot = 0;
    frame = IMG_regular_explosion0*4;
    texture = Textures[frame/4];
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    dest.w/=2; dest.h/=2;
}
bool Mob::isOver(){
    return (dest.y - dest.h > GAME_HEIGHT) || (dest.x > SCREEN_WIDTH) || (dest.x+dest.w < 0);
}
bool Mob::isAnimation(){
    return (frame == 0);
}
SDL_Rect Mob::getDest(){
    return dest;
}

// Powerup class
Pow::Pow(SDL_Rect position){  //Spawning 
    speedx = 0; speedy = 2;
    dest = position; 
    dest.x += dest.w/2; dest.y += dest.h/2;
    type = rand() % POW_count;
    texture = Textures[IMG_bolt + type];
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    dest.x -= dest.w/2; dest.y -= dest.h/2;
}
void Pow::activate(){
    switch (type)
    {
    case POW_bolt:
        BoostTime = SDL_GetTicks();
        Mix_PlayChannel(-1, Sounds[SND_bolt], 0);
        break;
    case POW_shield:
        player.shield += rand() % 20 + 10;
        if(player.shield >= MAX_SHIELD){
            player.shield = MAX_SHIELD;
        }
        Mix_PlayChannel(-1, Sounds[SND_shield], 0);
        break;
    default:
        break;
    }
}
bool Pow::isOver(){
    return dest.y > GAME_HEIGHT;
}
