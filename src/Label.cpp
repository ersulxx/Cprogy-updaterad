#include "Label.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Engine.h"


namespace demo {

    void Label::tick() {};

    Label::~Label() {
        SDL_DestroyTexture(texture);
    }

    void Label::draw() {
        SDL_RenderTexture(eng.getRen(), texture, NULL, & getRect());
    }

    void Label::setText(std::string newText) {
        text = newText;
        SDL_DestroyTexture(texture);
        SDL_Surface* surf = TTF_RenderText_Solid(eng.getFont(), text.c_str(), 0, {255, 255, 255} );
        texture = SDL_CreateTextureFromSurface(eng.getRen(), surf);
        SDL_DestroySurface(surf);
    }

    std::string Label::getText() const {
        return text;
    }

    LabelPtr Label::getLabelPtr(float x, float y, float w, float h, std::string txt) {
        return LabelPtr(new Label(x, y, w, h, txt));
    }

    Label::Label(float x, float y, float w, float h, std::string txt): Sprite(x, y, w, h), text(txt) {
        setText(text);
    }

}



