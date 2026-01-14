#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include "Constants.h"
#include <SDL3_ttf/SDL_ttf.h>


namespace demo {

    class Sprite;
    typedef std::shared_ptr<Sprite> SpritePtr;

    class Engine {
    public:
        Engine();
        ~Engine();

        SDL_Renderer* getRen() const;
        SDL_Window* getWin() const;
        TTF_Font* getFont() const;

        void add(SpritePtr spr);
        void remove(SpritePtr spr);
        void run();

        

        std::vector<SpritePtr> sprites, added, removed;


    private:
        SDL_Window* win = nullptr;
        SDL_Renderer* ren = nullptr;
        TTF_Font* font = nullptr;
        
        
    };

    extern Engine eng;

}