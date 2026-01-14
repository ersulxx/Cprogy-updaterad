#pragma once
#include "MoveableSprite.h"
#include <string>

/* FallingEnemy är en specifik typ av MoveableSprite som rör
sig nedåt på skärmen och kan orsaka att spelet tar slut */
class FallingEnemy : public demo::MoveableSprite
{

public:
    // Konstruktorn som tar emot bildsökväg, startposition och fall hastighet
    FallingEnemy(const std::string &img, float x, float y, float speed);
    void tick() override;
    // Hanterar vad som händer vid krock
    void onCollisionWith(demo::SpritePtr other) override;
    bool canTriggerGameOver() const override;

private:
    float speed;
};