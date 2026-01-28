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

typedef struct Ball Ball;

typedef struct Paddle {
  Rectangle Shape;
  Color PaddleColor;
  float targetY; // For AI paddle smooth interpolation
  Vector2 PreviousPosition;
  Vector2 RenderPosition;
  float timeAccumulator;
} Paddle;

void InitPaddle(Paddle *paddle, float x, float y, float width, float height,
                Color color);
void UpdatePlayerPaddle(Paddle *paddle, float Speed);
float AiVerticalStep(float offset_y, float speed, float dt, float dead_zone);
void UpdateAIPaddle(Paddle *paddle, float Speed, const Ball *ball);
void UpdatePlayer2Paddle(Paddle *paddle, float speed);
void DrawPaddle(const Paddle *paddle);

#endif // HYPER_PADDLE_PADDLE_H