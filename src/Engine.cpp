#include "Engine.h"
#include "Constants.h"
#include "Sprite.h"
#include "MoveableSprite.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <algorithm>

namespace demo {

    Engine::Engine()
    {
        // Initiera SDL VIDEO och AUDIO
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
        {
            std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
        if (!TTF_Init())
        {
            std::cerr << "TTF_Init failed: " << SDL_GetError() << std::endl;
        }

        // Skapa fönstret resizable så användaren kan ändra storlek
        win = SDL_CreateWindow("Space Wars", constants::gScreenWidth, constants::gScreenHeight, SDL_WINDOW_RESIZABLE);
        ren = SDL_CreateRenderer(win, NULL);

        font = TTF_OpenFont(constants::fontPath.c_str(), 24);
    }

    Engine::~Engine()
    {
        // Rensering alla listor vid avslutning
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

    // Lägg till och ta bort sprites
    void Engine::add(SpritePtr spr) { added.push_back(spr); }
    void Engine::remove(SpritePtr spr) { removed.push_back(spr); }
    
    SDL_Renderer* Engine::getRen() const { return ren; }
    SDL_Window* Engine::getWin() const { return win; }
    TTF_Font *Engine::getFont() const { return font; }

    void Engine::run()
    {
        const int FPS = 60;
        const int TICKINTERVAL = 1000 / FPS;
        bool running = true;

        while (running)
        {
            Uint64 nextTick = SDL_GetTicks() + TICKINTERVAL;
            SDL_Event event;

            while (SDL_PollEvent(&event))
            {
                switch(event.type) {
                    case SDL_EVENT_QUIT:
                        running = false;
                        break;

                    case SDL_EVENT_KEY_DOWN:
                    {
                        // Skicka tangentryck till alla MoveableSprites
                        for (SpritePtr spr : sprites) {
                            auto movable = std::dynamic_pointer_cast<MoveableSprite>(spr);
                            if (!movable) continue;
                            
                            switch(event.key.scancode) {
                                case SDL_SCANCODE_UP:    movable->onKeyUp();    break;
                                case SDL_SCANCODE_LEFT:  movable->onKeyLeft();  break;
                                case SDL_SCANCODE_RIGHT: movable->onKeyRight(); break;
                                case SDL_SCANCODE_DOWN:  movable->onKeyDown();  break;
                                default: break;
                            }
                        }
                    }
                    break;
                }
            }

            // 1. Uppdatera alla sprites
            for (SpritePtr spr : sprites)
                spr->tick();

            // 2. Hantera tillagda objekt
            for (SpritePtr spr : added)
                sprites.push_back(spr);
            added.clear();

            // 3. Kontrollerar förlusten
            for (SpritePtr spr : sprites)
            {
                if (spr->canTriggerGameOver())
                {
                    // Och kollar om det specifika objektet nått botten
                    if (spr->getRect().y > constants::gScreenHeight - 60)
                    {
                        // Rita en sista gång så man ser förlusten
                        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
                        SDL_RenderClear(ren);
                        for (SpritePtr s : sprites) s->draw();
                        SDL_RenderPresent(ren);

                        const SDL_MessageBoxButtonData buttons[] = {
                            {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Quit"},
                        };

                        const SDL_MessageBoxData messageboxdata = {
                            SDL_MESSAGEBOX_INFORMATION,
                            getWin(),
                            "Game Over",
                            "Spelet är slut!",
                            SDL_arraysize(buttons),
                            buttons,
                            NULL};

                        int buttonid;
                        SDL_ShowMessageBox(&messageboxdata, &buttonid);

                        running = false; // Stoppa loopen och stäng ner motorn
                        break;
                    }
                }
            }

            // 4. Ta bort döda (eller borttagna) objekt
            for (SpritePtr spr : removed)
            {
                auto it = std::find(sprites.begin(), sprites.end(), spr);
                if (it != sprites.end()) {
                    sprites.erase(it);
                }
            }
            removed.clear();

            // 5. KOLLISIONLOOP
            // Kontrollerar om MoveableSprites krockar med varandra
            for (SpritePtr sp1 : sprites) {
                auto ms1 = std::dynamic_pointer_cast<MoveableSprite>(sp1);
                if (!ms1) continue;
                
                for (SpritePtr sp2 : sprites) {
                    auto ms2 = std::dynamic_pointer_cast<MoveableSprite>(sp2);
                    // Kontrollerar att det inte är samma objekt
                    if (!ms2 || sp1 == sp2) continue;
                    
                    if (ms1->collidedWith(ms2))
                    {
                        ms1->onCollisionWith(ms2);
                        ms2->onCollisionWith(ms1);
                    }
                }
            }

            // 6. Rendera (Rita)
            SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
            SDL_RenderClear(ren);
            for (SpritePtr spr : sprites)
                spr->draw();
            SDL_RenderPresent(ren);

            // 7. FPS Delay
            Sint64 delay = nextTick - SDL_GetTicks();
            if (delay > 0)
                SDL_Delay(delay);
        }
    }

    // Skapa en global engine-instans
    Engine eng;
}