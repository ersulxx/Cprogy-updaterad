#pragma once
#include "Sprite.h"
#include <string>
#include <memory>

namespace gameEngine {

    class Label;
    typedef std::shared_ptr<Label> LabelPtr;

    class Label : public Sprite {

        public: 

        ~Label();

        void tick();

        void draw();

        void onResize(int newWidth, int newHeight) override;

        void setText(std::string newText);

        std::string getText() const;

        static LabelPtr getLabelPtr(float x, float y, float width, float height, std::string initialText);

        protected:
        Label(float x, float y, float width, float height, std::string initialText);

        private:
        std::string text;
        SDL_Texture* texture; //minneshantering sker i Label.cpp 
    };
}