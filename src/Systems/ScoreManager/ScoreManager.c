//
// Created by Squid on 11/4/2025.
//

#include "Systems/ScoreManager/ScoreManager.h"


void InitScore(Counter* counter, const int initialScore,
    const float posX, const float posY, const Color textColor, const float textSize) {

    counter->score = initialScore;
    counter->position.x = posX;
    counter->position.y = posY;
    counter->textColor = textColor;
    counter->textSize = textSize;
}

void DrawScore(const Counter* counter) {
    DrawText(TextFormat("%i", counter->score), (int)counter->position.x,
        (int)counter->position.y, (int)counter->textSize, counter->textColor);
}