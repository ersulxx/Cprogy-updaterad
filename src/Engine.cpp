#include "Engine.h"
#include "Sprite.h"
#include "MoveableSprite.h"
#include "Label.h"
#include "FallingEnemy.h"
#include "Rocketship.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <cstdlib>




namespace demo {

    class Background : public Sprite {
    public:
        Background() : Sprite(constants::background2_str, 0, 0) {}
        void tick() override {}
    };

    Engine::Engine()
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        {
            std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
        if (!TTF_Init())
        {
            std::cerr << "TTF_Init failed: " << SDL_GetError() << std::endl;
        }
        win = SDL_CreateWindow("Our Game", constants::gScreenWidth, constants::gScreenHeight, 0);
        ren = SDL_CreateRenderer(win, NULL);

        //2 engine ska vara i constant
        const std::string fontPath = constants::gResPath + "fonts/arial.ttf";
        font = TTF_OpenFont(fontPath.c_str(), 24);
    }

    Engine::~Engine()
    {
        sprites.clear();
        added.clear();
        removed.clear();

        if (font)
            TTF_CloseFont(font);
        TTF_Quit();
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
    }

    void Engine::add(SpritePtr spr) { added.push_back(spr); }
    void Engine::remove(SpritePtr spr) { removed.push_back(spr); }
    
    SDL_Renderer* Engine::getRen() const { return ren; }
    SDL_Window* Engine::getWin() const { return win; }
    TTF_Font *Engine::getFont() const { return font; }

    void Engine::run()
    {
        Uint64 lastSpawnTime = SDL_GetTicks();
        Uint64 spawnInterval = 2000;
        const int FPS = 60;
        const int TICKINTERVAL = 1000 / FPS;
        bool running = true;

        while (running)
        {
            Uint64 nextTick = SDL_GetTicks() + TICKINTERVAL;
            SDL_Event event;

            while (SDL_PollEvent(&event))
            {
                //1
                switch(event.type) {

                    case SDL_EVENT_QUIT:
                    running = false;
                    break;

                    case SDL_EVENT_KEY_DOWN:
                    {
                        for (SpritePtr spr : sprites) {
                            auto movable = std::dynamic_pointer_cast<MoveableSprite>(spr);
                            if (!movable) continue;
                            
                            switch(event.key.scancode) {
                                case SDL_SCANCODE_UP:
                                    movable->onKeyUp();
                                    break;
                                case SDL_SCANCODE_LEFT:
                                    movable->onKeyLeft();
                                    break;
                                case SDL_SCANCODE_RIGHT:
                                    movable->onKeyRight();
                                    break;
                                case SDL_SCANCODE_DOWN:
                                    movable->onKeyDown();
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                    break;

                } // switch
            }

            Uint64 currentTime = SDL_GetTicks();
            if (currentTime > lastSpawnTime + spawnInterval)
            {
                float randomX = static_cast<float>(std::rand() % (constants::gScreenWidth - 100));
                this->add(std::make_shared<::FallingEnemy>(constants::alien_str, randomX, -100.0f, 2.0f + (std::rand() % 4)));
                lastSpawnTime = currentTime;
            }

            for (SpritePtr spr : sprites)
                spr->tick();

            for (SpritePtr spr : added)
                sprites.push_back(spr);
            added.clear();

            // KONTROLLERA FÖRLUST
            for (SpritePtr spr : sprites)
            {
                if (std::dynamic_pointer_cast<::FallingEnemy>(spr))
                {
                    if (spr->getRect().y > constants::gScreenHeight - 60)
                    {
                        SDL_RenderClear(ren);
                        for (SpritePtr s : sprites)
                            s->draw();
                        SDL_RenderPresent(ren);

                        const SDL_MessageBoxButtonData buttons[] = {
                            {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Retry"},
                            {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "Quit"},
                        };

                        const SDL_MessageBoxData messageboxdata = {
                            SDL_MESSAGEBOX_INFORMATION,
                            getWin(),
                            "Game Over",
                            "En fiende nådde botten! Vad vill du göra?",
                            SDL_arraysize(buttons),
                            buttons,
                            NULL};

                        int buttonid;
                        if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0)
                        {
                            SDL_Log("error displaying message box");
                            running = false; 
                        }

                        if (buttonid == 1)
                        {

                            running = false;
                        }
                        else
                        {
                            // Användaren klickade på "Retry" (id 0) eller stängde rutan
                            sprites.clear();
                            added.clear();
                            removed.clear();
                            this->add(std::make_shared<Background>());
                            this->add(std::make_shared<Rocketship>());
                            lastSpawnTime = SDL_GetTicks();
                        }
                        break;
                    }
                }
            }

            for (SpritePtr spr : removed)
            {
                for (size_t pos = 0; pos < sprites.size(); pos++)
                {
                    if (spr == sprites[pos])
                    {
                        sprites.erase(sprites.begin() + pos);
                        break;
                    }
                }
            }
            removed.clear();

            for (SpritePtr sp1 : sprites) {
                auto m1 = std::dynamic_pointer_cast<MoveableSprite>(sp1);
                if (!m1) continue;
                
                for (SpritePtr sp2 : sprites) {
                    auto m2 = std::dynamic_pointer_cast<MoveableSprite>(sp2);
                    if (!m2) continue;
                    
                    if (sp1 != sp2 && m1->collidedWith(m2))
                    {
                        m1->onCollisionWith(m2);
                        m2->onCollisionWith(m1);
                    }
                }
            }

            SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
            SDL_RenderClear(ren);
            for (SpritePtr spr : sprites)
                spr->draw();
            SDL_RenderPresent(ren);

            Sint64 delay = nextTick - SDL_GetTicks();
            if (delay > 0)
                SDL_Delay(delay);
        }
    }

    Engine eng;

}