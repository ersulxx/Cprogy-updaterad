
#include "Bullet.h"
#include "Constants.h"
#include "Engine.h"
#include "FallingEnemy.h"
#include "Label.h"
#include <memory>
#include "UpdateScore.h"



Bullet::Bullet(float x, float y, float bulletSpeed) : demo::MoveableSprite(constants::bullet_str, x, y), bulletSpeed(bulletSpeed)
{

    getRect().w *= 0.05f;
    getRect().h *= 0.05f;
}

void Bullet::tick()
{
    move(0.0f, -bulletSpeed);

    if (getRect().y + getRect().h < 0)
    {
        demo::eng.remove(std::static_pointer_cast<demo::Sprite>(std::enable_shared_from_this<demo::Sprite>::shared_from_this()));
    }
}

void Bullet::onCollisionWith(demo::SpritePtr other)
{

    if (std::dynamic_pointer_cast<::FallingEnemy>(other))
    {
        demo::eng.remove(other);
        demo::eng.remove(shared_from_this());
        
        UpdateScore::increaseScore();
    }
}