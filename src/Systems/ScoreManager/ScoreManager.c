//
// Created by Squid on 11/4/2025.
//

#include "Systems/ScoreManager/ScoreManager.h"


void InitScore(Counter* counter, const int score, const float posX, const float posY, const Color color, const char* scoreText, const float textSize) {
    counter->score = score;
    counter->position.x = posX;
    counter->position.y = posY;
    counter->textColor = color;
    counter->text = scoreText;
    counter->textSize = textSize;
}

void DrawScore(const Counter* counter, int score , const float textSize, const Color textColor) {
    DrawText(TextFormat("%i", score), (int)counter->position.x,
        (int)counter->position.y, (int)textSize, textColor);
}
