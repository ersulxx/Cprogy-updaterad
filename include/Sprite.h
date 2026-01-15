#pragma once
#include <memory>
#include <string>
#include <SDL3/SDL.h>

namespace gameEngine
{

    // class Sprite;

    // typedef std::shared_ptr<Sprite> SpritePtr;

    class Sprite: public std::enable_shared_from_this<Sprite>
    {

    public:
        //systemet vet inte att objektet är av en subklass. Åtgärda detta används "virtuella destruktor"
        virtual ~Sprite();
        virtual void tick() = 0;

        //ritar image på skärmen på den position som anges av rect. Kan överskuggas
        virtual void draw();
        SDL_FRect &getRect();
        SDL_Texture* getTexture() const;

        //ändra storleken på bredden och höjden
        virtual void onResize(int newW, int newH) {}
        virtual bool canTriggerGameOver() const { return false; }
        
        //värdesemantik ska vara förbjuden för polymorfa klasser
        Sprite(const Sprite &other) = delete;
        const Sprite &operator=(const Sprite &other) = delete;

    protected:
        // gör inget särkskilt;
        Sprite() = default;

        // tar en filväg(image), två float för att sätta position;
        Sprite(std::string name, float x, float y);

        // pos och storlek för en rektangel (skapa sprite utan att ladda en textur direkt)
        Sprite(float x, float y, float w, float h); 

    private:
        SDL_FRect rect;
        
        //sparar "bilden"
        SDL_Texture *image; 
    };
    typedef std::shared_ptr<Sprite> SpritePtr;
}