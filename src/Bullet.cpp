
#include "Bullet.h"
#include "Constants.h"
#include "Engine.h"
#include "FallingEnemy.h"
#include "Label.h"
#include <memory>

//namespace std vet ej om den är nödvändig

extern int enemyHits;
extern demo::LabelPtr label2;

Bullet::Bullet(float x, float y, float speed): demo::MoveableSprite(constants::bullet_str, x, y), speed(speed) {

    getRect().w *= 0.05f;
    getRect().h *= 0.05f;
}

void Bullet::tick() {

    move(0.0f, -speed);

    if (getRect().y + getRect().h < 0) {
        demo::eng.remove(std::static_pointer_cast<demo::Sprite>(shared_from_this()));
    }
}

void Bullet::onCollisionWith(demo::MoveableSpritePtr other) {

    if (std::dynamic_pointer_cast<::FallingEnemy>(other)) {
        demo::eng.remove(other);
        demo::eng.remove(std::static_pointer_cast<demo::Sprite>(shared_from_this()));

        enemyHits++;
        label2->setText(std::to_string(enemyHits));
    }
}