#pragma once
#include "MoveableSprite.h"

namespace demo {    //Gör så att spelaren kan ändra storleken på skärmen 
    class Background : public MoveableSprite {
        public:
            Background(float start);
            void tick() ;
            void onResize(int newWidth, int newHeight);
    };
}