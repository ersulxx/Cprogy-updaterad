#include "Engine.h"
#include "Sprite.h"
#include "Rocketship.h"
#include "Background.h"
#include "FallingEnemy.h"
#include "Bullet.h"
#include "Label.h"
#include "CountHits.h"

using namespace std;
using namespace demo;
using namespace game;

//int enemyHits = 0;

//LabelPtr label;
//LabelPtr label2;

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

    // Skapa labels och lägg till i engine
    //label = Label::getLabelPtr(150, 150, 40, 50, "Antal nedskuttna:");
    //label2 = Label::getLabelPtr(200, 150, 40, 50, "0");
    //eng.add(label);
    //eng.add(label2);
    auto scoreLabel = demo::Label::getLabelPtr(500, 20, 120, 30, "Score: 0");
    demo::eng.add(scoreLabel);

    game::CountHits::setLabel(scoreLabel);
    
}


int main()
{
    setupGame();
    demo::eng.run();
    return 0;
}


/*int main(int argc, char* argv[]) {

    SpritePtr bg = std::make_shared<Background>();
    eng.add(bg);

    SpritePtr player = std::make_shared<Rocketship>();
    eng.add(player);

    SpritePtr e1 = std::make_shared<FallingEnemy>(constants::alien_str, 100, -40, 2.0f);
    SpritePtr e2 = std::make_shared<FallingEnemy>(constants::alien2_str, 300, -200, 1.5f);
    label = Label::getLabelPtr(150, 150, 40, 50, "Antal nedskuttna:");
    label2 = Label::getLabelPtr(200, 150, 40, 50, "0");
    
    eng.add(e1);
    eng.add(e2);
    eng.add(label);
    eng.add(label2);
    eng.run();
    
    return 0;
}*/