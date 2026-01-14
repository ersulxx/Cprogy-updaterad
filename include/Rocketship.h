#pragma once

#include "MoveableSprite.h"

class Rocketship : public demo::MoveableSprite {

    public:

    Rocketship();
    
    
    void tick() override;
    
    //tryck på pil uppåt
    void onKeyUp() override;
    
    //tryck på vänster pil
    void onKeyLeft() override;
    
    //tryck på höger pil
    void onKeyRight() override;

    private:
    //skjuter kullor
    void rocketshipFireBullet();
    

};