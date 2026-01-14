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

        //hanterar kollision, subklasserna kan hantera det
        virtual void onCollisionWith(SpritePtr other);
        
        
        ~MoveableSprite();
        
        //kollar om en kollision har skett
        bool collidedWith(MoveableSpritePtr other);

        //float värden för ändring av horesontelsla och vertikala värderna 
        void move(float dx, float dy);


        protected:
        MoveableSprite(std::string path, float x, float y);






    };
}