#include <string>
#include "UpdateScore.h"
using namespace std;



int UpdateScore::score = 0;
demo::LabelPtr UpdateScore::scoreLabel = nullptr;

void UpdateScore::increaseScore() {
    score++;
    if (scoreLabel) {
        scoreLabel->setText("Score: " + to_string(score));
    }
}

void UpdateScore::resetScore() {
    score = 0;
    if (scoreLabel) {
        scoreLabel->setText("Score: 0");
    }
}   
