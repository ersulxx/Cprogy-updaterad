#pragma once
#include "MovableSprite.h"

namespace demo {
    class Background : public MovableSprite {
        public:
            Background(float y);
            void tick() override;
            void onResize(int newW, int newH) override;
    };
}