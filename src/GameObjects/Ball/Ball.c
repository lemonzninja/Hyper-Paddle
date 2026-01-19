/****************************************************************
*              - Ball Game Object -
*  Created by Squid on 10/30/2025
****************************************************************/

#include "GameObjects/Ball/Ball.h"
#include <math.h>
#include "Systems/deltaTime.h"

static float RandomizeBallVerticalSpeed(const float velocity) {
    const float range = velocity * 0.65f;
    const float randomScale = (float)GetRandomValue(-(int)(range), (int)(range));
    float vertical = randomScale;
    if (fabsf(vertical) < velocity * 0.2f) {
        vertical = (vertical < 0.0f ? -1.0f : 1.0f) * velocity * 0.25f;
    }
    return vertical;
}

void InitBall(Ball *ball, const float x, const float y, const float width, const float height, const float velocity, const Color color) {
    ball->Shape.x = x;
    ball->Shape.y = y;
    ball->Shape.width = width;
    ball->Shape.height = height;
    ball->BallColor = color;
    ball->Velocity.x = velocity;
    ball->Velocity.y = RandomizeBallVerticalSpeed(velocity);

    ball->isLeftSide = false;
    ball->isRightSide = false;

    ball->bounceSound = LoadSound("assets/soundFX/ballSound.wav");
}

void ResetBall(Ball* ball, const float x, const float y, const float velocity) {
    ball->Shape.x = x;
    ball->Shape.y = y;
    ball->Velocity.x = velocity;
    ball->Velocity.y = RandomizeBallVerticalSpeed(velocity);
    ball->isLeftSide = false;
    ball->isRightSide = false;
}

void UnloadBall(const Ball* ball) {
    UnloadSound(ball->bounceSound);
}

void UpdateBall(Ball *ball) {
    ball->Shape.x += -ball->Velocity.x * deltaTime();
    ball->Shape.y += ball->Velocity.y * deltaTime();
}

void DrawBall(const Ball *ball) {
    // Draw the ball
    DrawRectangleRec(ball->Shape, ball->BallColor);
}

void HandleVerticalBounds(Ball *ball) {
    if (ball->Shape.y <= 0.0f) {
        ball->Shape.y = 0.0f;
        ball->Velocity.y = -ball->Velocity.y;
        //PlaySound(ball->bounceSound);
    }

    const float screenBottomSide = (float)GetScreenHeight();
    const float ballBottomSide = ball->Shape.y + ball->Shape.height;

    if (ballBottomSide >= screenBottomSide) {
        ball->Shape.y = screenBottomSide - ball->Shape.height;
        ball->Velocity.y = -ball->Velocity.y;
        //PlaySound(ball->bounceSound);
    }
}

void ballDetectGoal(Ball *ball) {
    // if the ball hits the left edge have aiScore go up 1.
    if (ball->Shape.x <= 0.0f) {
        ball->isLeftSide = true;
    }


    // if the ball hits the right edge have playerScore go up 1.
    if (ball->Shape.x >= (float) GetScreenWidth() - ball->Shape.width) {
        ball->isRightSide = true;
    }
}