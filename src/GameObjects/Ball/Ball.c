/****************************************************************
*              - Ball Game Object -
*  Created by Squid on 10/30/2025
****************************************************************/

#include "GameObjects/Ball/Ball.h"
#include <math.h>
#include "Systems/deltaTime.h"

static float RandomizeBallVerticalSpeed(const float velocity) {
    const float speed = fabsf(velocity);
    const float range = speed * 0.65f;
    const float randomScale = (float)GetRandomValue(0, 1000) / 1000.0f;
    float vertical = (randomScale * 2.0f - 1.0f) * range;
    if (fabsf(vertical) < speed * 0.2f) {
        vertical = (vertical < 0.0f ? -1.0f : 1.0f) * speed * 0.25f;
    }
    return vertical;
}

void InitBall(Ball *ball, const float x, const float y, const float width, const float height, const float velocity, const Color color) {
    const float direction = GetRandomValue(0, 1) == 0 ? -1.0f : 1.0f;

    ball->Shape.x = x;
    ball->Shape.y = y;
    ball->Shape.width = width;
    ball->Shape.height = height;
    ball->BallColor = color;
    ball->Velocity.x = direction * fabsf(velocity);
    ball->Velocity.y = RandomizeBallVerticalSpeed(velocity);

    ball->bounceSound = LoadSound("assets/soundFX/ballSound.wav");
}

void ResetBall(Ball *ball, const float x, const float y, const float velocity) {
    const float direction = GetRandomValue(0, 1) == 0 ? -1.0f : 1.0f;

    ball->Shape.x = x;
    ball->Shape.y = y;
    ball->Velocity.x = direction * fabsf(velocity);
    ball->Velocity.y = RandomizeBallVerticalSpeed(velocity);
}

void UnloadBall(const Ball *ball) {
    UnloadSound(ball->bounceSound);
}

void UpdateBall(Ball *ball) {
    ball->Shape.x += ball->Velocity.x * deltaTime();
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

BallGoal DetectBallGoal(const Ball *ball) {
    // if the ball hits the left edge have aiScore go up 1.
    if (ball->Shape.x <= 0.0f) {
        return BALL_GOAL_LEFT;
    }

    // if the ball hits the right edge have playerScore go up 1.
    if (ball->Shape.x >= (float)GetScreenWidth() - ball->Shape.width) {
        return BALL_GOAL_RIGHT;
    }

    return BALL_GOAL_NONE;
}