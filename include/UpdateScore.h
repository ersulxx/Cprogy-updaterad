#pragma once
#include "Engine.h"
#include "Sprite.h"
#include "Label.h"


using namespace gameEngine;

class UpdateScore {
        
    public:
    //sätter värdet score till noll
    static void setLabel(gameEngine::LabelPtr label) { scoreLabel = label; }
    
    static void increaseScore();
    static void resetScore();
    
    private:
    static int score;
    //som har värde numret
    static gameEngine::LabelPtr scoreLabel;
}; 
