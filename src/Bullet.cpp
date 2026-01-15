
#include "Bullet.h"
#include "Constants.h"
#include "Engine.h"
#include "FallingEnemy.h"
#include "Label.h"
#include <memory>
#include "UpdateScore.h"



Bullet::Bullet(float x, float y, float bulletSpeed) : gameEngine::MoveableSprite(constants::bullet_str, x, y), bulletSpeed(bulletSpeed)
{

    getRect().w *= 0.05f;
    getRect().h *= 0.05f;
}

void Bullet::tick()
{
    move(0.0f, -bulletSpeed);

    if (getRect().y + getRect().h < 0)
    {
        gameEngine::eng.remove(std::static_pointer_cast<gameEngine::Sprite>(std::enable_shared_from_this<gameEngine::Sprite>::shared_from_this()));
    }
}

void Bullet::onCollisionWith(gameEngine::SpritePtr other)
{

    if (std::dynamic_pointer_cast<::FallingEnemy>(other))
    {
        gameEngine::eng.remove(other);
        gameEngine::eng.remove(shared_from_this());
        
        UpdateScore::increaseScore();
    }
}