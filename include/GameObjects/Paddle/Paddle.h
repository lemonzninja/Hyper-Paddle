/****************************************************************
*              - Paddle Game Object -
*  The paddle for the player and AI.
*  The paddle can only move up and down.
*  The paddle shod be clamped between two points on the screen.
*  And the paddle can't leave the screen.
*  Created by Squid on 10/28/2025
****************************************************************/

#ifndef HYPER_PADDLE_PADDLE_H
#define HYPER_PADDLE_PADDLE_H

#include "raylib.h"

typedef struct Paddle {
    Rectangle Shape;
    Color PaddleColor;
}Paddle;

void InitPaddle(Paddle *paddle,
                float x,
                float y,
                float width,
                float height,
                Color paddleColor);
void UpdatePaddle(Paddle* paddle);
void UpdatePlayerPaddle(Paddle* paddle, float Speed);
void UpdateAIPaddle(Paddle* paddle, float Speed);

void DrawPaddle(const Paddle *paddle);

#endif //HYPER_PADDLE_PADDLE_H