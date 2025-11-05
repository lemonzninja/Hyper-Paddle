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
    const char* text;
    float textSize;

} Counter;

void InitScore(Counter* counter,
                int score,
                float posX,
                float posY,
                Color color,
                const char* scoreText,
                float textSize);

void DrawScore(const Counter* counter, int score, float textSize, Color textColor);


#endif //HYPER_PADDLE_SCOREMANAGAER_H
