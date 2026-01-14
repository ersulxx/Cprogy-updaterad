
#include "Engine.h"
#include "Sprite.h"
#include "Label.h"
#pragma once


using namespace demo;

class UpdateScore {
        
    public:
    //sätter värdet score till noll
    static void setLabel(demo::LabelPtr label) { scoreLabel = label; }
    
    static void increaseScore();
    static void resetScore();
    
    private:
    static int score;
    //som har värde numret
    static demo::LabelPtr scoreLabel;
}; 
