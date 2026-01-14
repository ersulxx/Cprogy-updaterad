#pragma once
#include "MoveableSprite.h"
#include <string>

class FallingEnemy : public demo::MoveableSprite
{

public:
    FallingEnemy(const std::string &img, float x, float y, float speed);
    void tick() override;
    void onCollisionWith(demo::SpritePtr other) override;
    bool canTriggerGameOver() const override;

private:
    float speed;
};