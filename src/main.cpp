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


class EnemySpawner : public demo::Sprite {
public:
    Uint64 lastSpawn = 0;
    const Uint64 interval = 2000;

    EnemySpawner() : demo::Sprite(0, 0, 0, 0) {
        lastSpawn = SDL_GetTicks();
    }

    void tick() override {
        Uint64 now = SDL_GetTicks();
        if (now > lastSpawn + interval) {
            float x = static_cast<float>(std::rand() % (constants::gScreenWidth - 100));
            // Här skapas fienden och läggs till i motorn
            eng.add(std::make_shared<FallingEnemy>(constants::alien_str, x, -50, 2.0f + (std::rand() % 3)));
            eng.add(std::make_shared<FallingEnemy>(constants::alien2_str, x, -50, 2.0f + (std::rand() % 3)));
            lastSpawn = now;
        }
    }
    // Vi skriver över draw så att spawnern inte försöker rita något
    void draw() override {} 
};


void setupGame()
{
    // Skapa bakgrunder och lägg till i engine
    auto background1 = std::make_shared<demo::Background>(0);
    auto background2 = std::make_shared<demo::Background>(-constants::gScreenHeight);
    eng.add(background1);
    eng.add(background2);

    // Skapa en spelare(Rocketship) och lägg till i engine
    auto player = std::make_shared<Rocketship>();
    eng.add(player);

    // Skapa fiender och lägg till i engine
    auto enemy1 = std::make_shared<FallingEnemy>(constants::alien_str, 100, -40, 2.0f);
    auto enemy2 = std::make_shared<FallingEnemy>(constants::alien2_str, 300, -200, 1.5f);
    eng.add(enemy1);
    eng.add(enemy2);

    auto spawner = std::make_shared<EnemySpawner>();
    eng.add(spawner);

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
