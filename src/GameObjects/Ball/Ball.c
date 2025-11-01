/****************************************************************
*              - Ball Game Object -
*  Created by Squid on 10/30/2025
****************************************************************/

#include "GameObjects/Ball/Ball.h"

#include <stdio.h>

#include "Systems/deltaTime.h"



void InitBall(Ball *ball, const float x, const float y, const float width, const float height, const float velocity, const Color ballColor) {
    ball->Shape.x = x;
    ball->Shape.y = y;
    ball->Shape.width = width;
    ball->Shape.height = height;
    ball->BallColor = ballColor;
    ball->Velocity.x = velocity;
    ball->Velocity.y = velocity;
}

void UpdateBall(Ball *ball) {
    ball->Shape.x += -ball->Velocity.x * deltaTime();
    ball->Shape.y += ball->Velocity.y * deltaTime();
}

void DrawBall(const Ball *ball) {
    // Draw the ball
    DrawRectangleRec(ball->Shape, ball->BallColor);
}

void HandleHorizontalBounds(Ball *ball) {
    // Left edge
    if (ball->Shape.x <= 0.0f - ball->Shape.width) {
        ball->Shape.x = 0.0f;
        ball->Velocity.x = -ball->Velocity.x;
    }

    // Store the right side of the screen as a variable.
    const float screenRightSide = (float)GetScreenWidth();

    // Get the right side of the ball and
    const float ballsRightSide = ball->Shape.x + ball->Shape.width;

    // If the balls right is the same as the right edge.
    if (ballsRightSide >= screenRightSide) {
        // set the balls right side to the screens right side.
        ball->Shape.x = screenRightSide - ball->Shape.width;
        // revers the balls velocity.
        ball->Velocity.x = -ball->Velocity.x;
    }
}

void HandleVerticalBounds(Ball *ball) {
    if (ball->Shape.y <= 0.0f) {
        ball->Shape.y = 0.0f;
        ball->Velocity.y = -ball->Velocity.y;
    }

    const float screenBottomSide = (float)GetScreenHeight();
    const float ballBottomSide = ball->Shape.y - ball->Shape.height;

    if (ball->Shape.y >= screenBottomSide) {
        ball->Shape.y = ballBottomSide - ball->Shape.height;
        ball->Velocity.y = -ball->Velocity.y;
    }
}