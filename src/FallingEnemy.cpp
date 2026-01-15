#include "FallingEnemy.h"
#include "../include/Constants.h"
#include "Bullet.h"
#include <cstdlib>


// Konstruktorn sätter bild, startposition och hastighet
FallingEnemy::FallingEnemy(const std::string &img, float x, float y, float speed) : gameEngine::MoveableSprite(img, x, y), speed(speed)
{

    // Skalar ner storleken på fienden till 10% av originalstorleken
    getRect().w *= 0.10f;
    getRect().h *= 0.10f;
}

// Uppdaterar fiendens position(varje frame)
void FallingEnemy::tick()
{
    move(0.0f, speed);

    if (getRect().y > constants::gScreenHeight)
    {
        float newY = -getRect().h; // Starta precis ovanför skärmen
        float newX = static_cast<float>(std::rand() % (constants::gScreenWidth - 64));
        move(newX - getRect().x, newY - getRect().y);
    }
}

// Hanterar vad som händer när fienden krockar/kolliderar med något
void FallingEnemy::onCollisionWith(gameEngine::SpritePtr other)
{
    // Kontrolleras om det vi krockade med är en Bullet
    if (std::dynamic_pointer_cast<::Bullet>(other))
    {
        /* Istället att ta bort fienden från spelet, återställs dess position
        till toppen av skärmen(Objekt återanvändning) */
        getRect().y = -getRect().h;
        getRect().x = static_cast<float>(std::rand() % (constants::gScreenWidth - 64));
    }
}


// Denna funktion indikerar att spelaren förlorar om denna fiende når botten av skärmen
bool FallingEnemy::canTriggerGameOver() const
{
    return true;
}