#include "Rocketship.h"
#include "Constants.h"
#include "Bullet.h"
#include "Engine.h"
#include "Sprite.h"

Rocketship::Rocketship() : demo::MoveableSprite(constants::rocketship_str, 0, 0) {

    getRect().w = 64.f;
    getRect().h = 64.f;

    getRect().x = (constants::gScreenWidth / 2.0f) - (getRect().w / 2.0f);
    getRect().y = constants::gScreenHeight - getRect().h - 20.0f;
}

void Rocketship::tick() {

    int numkeys;
    const bool* keystate = SDL_GetKeyboardState(&numkeys);

    if( keystate[SDL_SCANCODE_UP] ) {
        onKeyUp();
    }
    if ( keystate[SDL_SCANCODE_LEFT] ) {
        onKeyLeft();
    }
    if ( keystate[SDL_SCANCODE_RIGHT] ) {
        onKeyRight();
    }
}


void Rocketship::onKeyUp() {
    shoot();
}
    

void Rocketship::onKeyLeft() {

    if ( getRect().x > 0 ) {
        move(-4, 0);
    }
}
    

void Rocketship::onKeyRight() {

    if ( getRect().x + getRect().w < constants::gScreenWidth) {
        move(4, 0);
    }
}

void Rocketship::shoot() {
    

    float bulletX = getRect().x + (getRect().w / 12);
    float bulletY = getRect().y;

    if (bulletY > 0) {
        auto bullet = std::make_shared<Bullet>(bulletX, bulletY, 10.0f);
        demo::eng.add(bullet);
    }
}