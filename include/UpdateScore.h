
#include "Engine.h"
#include "Sprite.h"
#include "Label.h"
#pragma once


using namespace demo;

class UpdateScore {
        
    public:
    static void setLabel(demo::LabelPtr label) { scoreLabel = label; }
    static void increaseScore();
    static void resetScore();
    
    private:
    static int score;
    static demo::LabelPtr scoreLabel;
}; 
