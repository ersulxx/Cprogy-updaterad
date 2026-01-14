#pragma once
#include "MoveableSprite.h"

namespace demo {
    class Background : public MoveableSprite {
        public:
            Background(float y);
            void tick() ;
            void onResize(int newW, int newH);
    };
}