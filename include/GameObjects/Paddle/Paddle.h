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

// Forward declaration of Ball to avoid circular dependency if Ball.h includes Paddle.h
// But currently Ball.h doesn't include Paddle.h.
// To be safe and clean, we can just use struct Ball* or include Ball.h.
// Looking at includes, Ball.h is separate.
// I will verify includes. Paddle.h currently only includes raylib.h.
// I'll add a forward declaration to avoid including the whole header if not needed,
// but for the function signature `const Ball* ball`, I need `Ball` type defined or forward declared.
typedef struct Ball Ball;

typedef struct Paddle {
    Rectangle Shape;
    Color PaddleColor;
    float targetY; // For AI paddle smooth interpolation
}Paddle;


void InitPaddle(Paddle *paddle,
                float x,
                float y,
                float width,
                float height,
                Color color);
void UpdatePlayerPaddle(Paddle* paddle, float Speed);
float ai_vertical_step(float offset_y, float speed, float dt, float dead_zone);
void UpdateAIPaddle(Paddle* paddle, float Speed, const Ball* ball);

void DrawPaddle(const Paddle *paddle);

#endif //HYPER_PADDLE_PADDLE_H