#pragma once

#include "MoveableSprite.h"

class Rocketship : public demo::MoveableSprite {

    public:

    Rocketship();
    
    
    void tick() override;
    
    void onKeyUp() override;
    
    void onKeyLeft() override;
    
    void onKeyRight() override;

    private:
    void shoot();
    

};