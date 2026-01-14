#pragma once

#include "MoveableSprite.h"
#include <memory>

class Bullet : public demo::MoveableSprite {

    public:
    
    Bullet(float x, float y, float speed);
    
    void tick() override;

    void onCollisionWith(demo::MoveableSpritePtr other) override;

    private:
    float speed;

};