#pragma once

#include "MoveableSprite.h"
#include <memory>

class Bullet : public demo::MoveableSprite {

    public:
    
    Bullet(float x, float y, float bulletSpeed); //x=horistontellt, y=vertikalt
    
    void tick() override;

    void onCollisionWith(demo::SpritePtr other) override;

    private:
    float bulletSpeed;

};