#pragma once

#include "Sprite.h"
#include <memory>
#include <string>
#include <SDL3/SDL.h>

namespace demo {

    class MoveableSprite;

    typedef std::shared_ptr<MoveableSprite> MoveableSpritePtr;

    class MoveableSprite : public Sprite {

        public:

        static MoveableSpritePtr getMoveableSprite(std::string path, float x, float y);

        virtual void tick() override;

        virtual void onKeyUp();

        virtual void onKeyLeft();

        virtual void onKeyRight();

        virtual void onKeyDown();

        virtual void onCollisionWith(SpritePtr other);
        
        
        ~MoveableSprite();
        
        bool collidedWith(MoveableSpritePtr other);

        void move(float dx, float dy);


        protected:
        MoveableSprite(std::string path, float x, float y);






    };
}