
#include "Bullet.h"
#include "Constants.h"
#include "Engine.h"
#include "FallingEnemy.h"
#include "Label.h"
#include <memory>
#include "CountHits.h"

// namespace std vet ej om den är nödvändig

//int enemyHits=0;
//demo::LabelPtr label2=nullptr;



Bullet::Bullet(float x, float y, float speed) : demo::MoveableSprite(constants::bullet_str, x, y), speed(speed)
{

    getRect().w *= 0.05f;
    getRect().h *= 0.05f;
}

void Bullet::tick()
{

    move(0.0f, -speed);

    if (getRect().y + getRect().h < 0)
    {
        demo::eng.remove(std::static_pointer_cast<demo::Sprite>(std::enable_shared_from_this<demo::Sprite>::shared_from_this()));
    }
}

void Bullet::onCollisionWith(demo::SpritePtr other)
{

    if (std::dynamic_pointer_cast<::FallingEnemy>(other))
    {
        //auto explosion = std::make_shared<demo::Explosion>(getRect().x, getRect().y);
       // demo::eng.add(explosion);


        demo::eng.remove(other);
        demo::eng.remove(shared_from_this());
        game::CountHits::funk();

        //enemyHits++;
        //label2->setText(std::to_string(enemyHits));
    }
}