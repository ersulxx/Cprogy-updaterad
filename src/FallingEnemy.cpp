#include "FallingEnemy.h"
#include "../include/Constants.h"
#include "Bullet.h"
#include <cstdlib>

FallingEnemy::FallingEnemy(const std::string &img, float x, float y, float speed): demo::MoveableSprite(img, x, y), speed(speed) {

    getRect().w *= 0.10f;
    getRect().h *= 0.10f;
}

void FallingEnemy::tick() {

    move(0.0f, speed);

    if (getRect().y > constants::gScreenHeight) {
        
        float newY = -getRect().h;

        float newX = static_cast<float> (std::rand() % (constants::gScreenWidth - 64));

        move(newX - getRect().x, newY - getRect().y);
    }
}

void FallingEnemy::onCollisionWith(demo::SpritePtr other) {

    if (std::dynamic_pointer_cast<::Bullet>(other)) {
        getRect().y = -getRect().h;
        getRect().x = static_cast<float>(std::rand() % (constants::gScreenWidth - 64));
    }
}