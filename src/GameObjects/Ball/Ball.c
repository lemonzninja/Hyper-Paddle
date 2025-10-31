//
// Created by Squid on 10/30/2025.
//

#include "GameObjects/Ball/Ball.h"

void InitBall(Ball *ball, const float x, const float y, const float width, const float height, const float velocity, const Color ballColor) {
    ball->Shape.x = x;
    ball->Shape.y = y;
    ball->Shape.width = width;
    ball->Shape.height = height;
    ball->BallColor = ballColor;
    ball->Velocity.x = velocity;
}

void UpdateBall(Ball *ball) {
    // move the ball to the right.
    ball->Shape.x += ball->Velocity.x;
}

void DrawBall(const Ball *ball) {
    // Draw the ball
    DrawRectangleRec(ball->Shape, ball->BallColor);
}
