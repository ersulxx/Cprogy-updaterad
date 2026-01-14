#pragma once
#include "Sprite.h"
#include <string>
#include <memory>

namespace demo {

    class Label;
    typedef std::shared_ptr<Label> LabelPtr;

    class Label : public Sprite {

        public:

        

        ~Label();

        void tick();

        void draw();

        void onResize(int newW, int newH) override;

        void setText(std::string newText);

        std::string getText() const;

        static LabelPtr getLabelPtr(float x, float y, float w, float h, std::string txt);

        protected:
        Label(float x, float y, float w, float h, std::string txt);

        private:
        std::string text;
        SDL_Texture* texture;
    };
}