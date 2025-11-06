//
// Created by Squid on 11/4/2025.
//

#ifndef HYPER_PADDLE_SCOREMANAGAER_H
#define HYPER_PADDLE_SCOREMANAGAER_H

#include "raylib.h"

// a struct for the score counter.
typedef struct Counter {
    int score;
    Vector2 position;
    Color textColor;
    float textSize;
} Counter;

void InitScore(Counter* counter, int initialScore,
    float posX, float posY, Color textColor, float textSize);
void DrawScore(const Counter* counter);


#endif //HYPER_PADDLE_SCOREMANAGAER_H
