#include "Label.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Engine.h"


namespace demo {

    void Label::tick() {};

    Label::~Label() {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }

    void Label::draw() {
        SDL_RenderTexture(eng.getRen(), texture, NULL, & getRect());
    }

    void Label::setText(std::string newText) {
        text = newText;
        if (texture) {
            SDL_DestroyTexture(texture);
        }
        SDL_Surface* surf = TTF_RenderText_Solid(eng.getFont(), text.c_str(), 0, {255, 255, 255} );
        texture = SDL_CreateTextureFromSurface(eng.getRen(), surf);
        SDL_DestroySurface(surf);
    }

    std::string Label::getText() const {
        return text;
    }

    LabelPtr Label::getLabelPtr(float x, float y, float width, float height, std::string txt) {
        return LabelPtr(new Label(x, y, width, height, txt));
    }

    Label::Label(float x, float y, float width, float height, std::string txt): Sprite(x, y, width, height), text(txt), texture(nullptr) {
        getRect().w = width;
        getRect().h = height;
        setText(text);
    }

    void Label::onResize(int newWidth, int newHeight)
    {
        getRect().x = newWidth - getRect().w - 20.0f;
        getRect().y = 20.0f;
    }

}



