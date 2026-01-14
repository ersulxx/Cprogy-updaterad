#include "Background.h"
#include "Engine.h"

namespace demo
{
    Background::Background(float start) : MoveableSprite(constants::background2_str, 0, start)
    {
        getRect().w = static_cast<float>(constants::gScreenWidth);
        getRect().h = static_cast<float>(constants::gScreenHeight) + 2.0f;
    }

    void Background::tick()
    {
        float backgroundMovingSpeed = 1.0f;
        getRect().y += backgroundMovingSpeed;
        if (getRect().y >= constants::gScreenHeight)
        {
            getRect().y -= constants::gScreenHeight * 2;
        }
    }

    void Background::onResize(int newWidth, int newHeight)
    {
        getRect().w = static_cast<float>(newWidth);
        getRect().h = static_cast<float>(newHeight);
    }
}