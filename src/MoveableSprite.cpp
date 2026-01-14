#include "MoveableSprite.h"
#include "Label.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Engine.h"
#include "Sprite.h"

namespace demo {

    void MoveableSprite::tick() {}
    
    void MoveableSprite::onKeyUp() {}
    
    void MoveableSprite::onKeyLeft() {}
    
    void MoveableSprite::onKeyRight() {}
    
    void MoveableSprite::onKeyDown() {}
    
    void MoveableSprite::onCollisionWith(SpritePtr other) {}

    


    MoveableSprite::~MoveableSprite() {}

    bool MoveableSprite::collidedWith(MoveableSpritePtr other) {
        return SDL_HasRectIntersectionFloat(&getRect(), &other->getRect());
    }

    void MoveableSprite::move(float dx, float dy) { getRect().x += dx; getRect().y += dy; }

    MoveableSprite::MoveableSprite(std::string path, float x, float y): Sprite(path, x, y) {}

    MoveableSpritePtr getMoveableSprite(std::string path, float x, float y) {
        return MoveableSpritePtr(new MoveableSprite(path, x, y));
    }

}