#include "Engine.h"
#include "Sprite.h"
#include "Rocketship.h"
#include "Background.h"
#include "FallingEnemy.h"
#include "Bullet.h"
#include "Label.h"
#include "UpdateScore.h"

using namespace std;
using namespace demo;
using namespace game;


void setupGame()
{
    // Skapa bakgrunder och lägg till i engine
    auto bg1 = std::make_shared<demo::Background>(0);
    auto bg2 = std::make_shared<demo::Background>(-constants::gScreenHeight);
    eng.add(bg1);
    eng.add(bg2);

    // Skapa en spelare(Rocketship) och lägg till i engine
    auto player = std::make_shared<Rocketship>();
    eng.add(player);

    // Skapa fiender och lägg till i engine
    auto e1 = std::make_shared<FallingEnemy>(constants::alien_str, 100, -40, 2.0f);
    auto e2 = std::make_shared<FallingEnemy>(constants::alien2_str, 300, -200, 1.5f);
    eng.add(e1);
    eng.add(e2);

    auto scoreLabel = demo::Label::getLabelPtr(500, 20, 120, 30, "Score: 0");
    eng.add(scoreLabel);

    UpdateScore::setLabel(scoreLabel);    
}


int main()
{
    setupGame();
    demo::eng.run();
    return 0;
}
