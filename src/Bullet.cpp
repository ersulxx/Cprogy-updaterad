
#include "Bullet.h"
#include "Constants.h"
#include "Engine.h"
#include "FallingEnemy.h"
#include "Label.h"
#include <memory>

// namespace std vet ej om den är nödvändig

extern int enemyHits;
extern demo::LabelPtr label2;

namespace demo
{
    class Explosion : public MoveableSprite // Implementerar en explosionseffekt när en fiende träffas av en bullet
    {
    public:
        Uint64 spawnTime;
        const Uint64 duration = 250;

        Explosion(float x, float y) : MoveableSprite(constants::explosion_str, x, y)
        {
            spawnTime = SDL_GetTicks();
            getRect().w = 40;
            getRect().h = 40;
            SDL_SetTextureBlendMode(getTexture(), SDL_BLENDMODE_BLEND); //Det gör att bilden kan ha transparens
        }

        void tick() override
        {
            Uint64 elapsed = SDL_GetTicks() - spawnTime; //Tidsräknaren, hur många millisekunder som gått sedan explosionen skapades

            float progress = (float)elapsed / duration;
            int alpha = (int)(255 * (1.0f - progress));
            if (alpha < 0)
                alpha = 0;
            SDL_SetTextureAlphaMod(getTexture(), (Uint8)alpha); //Skickar instruktionen för att rita bilden med  den genomskinligheten

            getRect().w += 0.8f;
            getRect().h += 0.8f;
            getRect().x -= 0.4f;
            getRect().y -= 0.4f;

            if (elapsed >= duration)
            {
                eng.remove(this-> shared_from_this());
            }
        }
    };

}

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
        demo::eng.remove(std::static_pointer_cast<demo::Sprite>(this-> shared_from_this()));
    }
}

void Bullet::onCollisionWith(demo::MoveableSpritePtr other)
{

    if (std::dynamic_pointer_cast<::FallingEnemy>(other))
    {
        auto explosion = std::make_shared<demo::Explosion>(getRect().x, getRect().y);
        demo::eng.add(explosion);


        demo::eng.remove(other);
        demo::eng.remove(std::static_pointer_cast<demo::Sprite>(this-> shared_from_this()));

        enemyHits++;
        label2->setText(std::to_string(enemyHits));
    }
}