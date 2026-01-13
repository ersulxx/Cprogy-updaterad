#pragma once

#include "MoveableSprite.h"
#include <memory>

class Bullet : public demo::MoveableSprite, public std::enable_shared_from_this<Bullet> {

    public:
    
    Bullet(float x, float y, float speed);
    
    void tick() override;

    void onCollisionWith(demo::MoveableSpritePtr other) override;

    private:
    float speed;

};