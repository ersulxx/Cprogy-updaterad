#include "Background.h"
#include "Engine.h"

namespace demo
{
    Background::Background(float y) : MoveableSprite(constants::background2_str, 0, y)
    {
        getRect().w = static_cast<float>(constants::gScreenWidth);
        getRect().h = static_cast<float>(constants::gScreenHeight) + 2.0f;
    }

    void Background::tick()
    {
        float speed = 1.0f;
        getRect().y += speed;
        if (getRect().y >= constants::gScreenHeight)
        {
            getRect().y -= constants::gScreenHeight * 2;
        }
    }

    void Background::onResize(int newW, int newH)
    {
        getRect().w = static_cast<float>(newW);
        getRect().h = static_cast<float>(newH);
    }
}