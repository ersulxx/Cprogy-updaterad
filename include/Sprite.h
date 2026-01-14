#pragma once
#include <memory>
#include <string>
#include <SDL3/SDL.h>

namespace demo
{

    // class Sprite;

    // typedef std::shared_ptr<Sprite> SpritePtr;

    class Sprite: public std::enable_shared_from_this<Sprite>
    {

    public:
        virtual ~Sprite();
        virtual void tick() = 0;
        virtual void draw();
        SDL_FRect &getRect();
        SDL_Texture* getTexture() const;
        virtual void onResize(int newW, int newH) {}
        virtual bool canTriggerGameOver() const { return false; }
        
        Sprite(const Sprite &other) = delete;
        const Sprite &operator=(const Sprite &other) = delete;

    protected:
        Sprite() = default;                         // gör inget särkskilt;
        Sprite(std::string name, float x, float y); // tar en filväg(image), två float för att sätta position;
        Sprite(float x, float y, float w, float h); // pos och storlek för en rektangel (skapa sprite utan att ladda en textur direkt)

    private:
        SDL_FRect rect;
        SDL_Texture *image;
    };
    typedef std::shared_ptr<Sprite> SpritePtr;
}