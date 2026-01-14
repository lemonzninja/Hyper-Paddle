/****************************************************************
*              - Paddle Game Object -
*  Created by Squid on 10/28/2025.
****************************************************************/

#include "GameObjects/Paddle/Paddle.h"
#include <tgmath.h>
#include "Systems/deltaTime.h"
#include "Systems/KeyboardManager/keyboardManager.h"
#include "GameObjects/Ball/Ball.h"
#include "Math/ComputeCenterYofRectangle.h"

void InitPaddle(Paddle *paddle, const float x, const float y, const float width, const float height, const Color color) {
    paddle->Shape.x = x;
    paddle->Shape.y = y;
    paddle->Shape.width = width;
    paddle->Shape.height = height;
    paddle->PaddleColor = color;
    paddle->targetY = y;
}

void UpdatePlayerPaddle(Paddle *paddle, const float Speed) {
    // Move up
    if (IsUpPressed()) {
        paddle->Shape.y -= Speed * deltaTime();
    }
    // move Down
    if (IsDownPressed()) {
        paddle->Shape.y += Speed * deltaTime();
    }

    // Keep paddle inside screen bounds (safety check)
    const float screenHeight = (float) GetScreenHeight();
    if (paddle->Shape.y < 0) {
        paddle->Shape.y = 0;
    }
    if (paddle->Shape.y + paddle->Shape.height > screenHeight) {
        paddle->Shape.y = screenHeight - paddle->Shape.height;
    }
}

// Decide the AI vertical step based on offset and dead zone
float ai_vertical_step(const float offset_y, const float speed, const float dt, const float dead_zone) {
    if (fabsf(offset_y) <= dead_zone) return 0.0f;
    // move up or down by speed * dt depending on the sign of offset
    return (offset_y > 0.0f ? 1.0f : -1.0f) * speed * dt;
}

void UpdateAIPaddle(Paddle *paddle, const float Speed, const Ball* ball) {
    const float screenHeight = (float) GetScreenHeight();
    const float maxY = screenHeight - paddle->Shape.height;

    const float dt = deltaTime();
    static float reactionTimer = 0.0f;
    const bool ballMovingRight = ball->Velocity.x < 0.0f;

    reactionTimer -= dt;
    if (ballMovingRight) {
        if (reactionTimer <= 0.0f) {
            const float speedX = fabsf(ball->Velocity.x);
            const float distanceX = paddle->Shape.x - (ball->Shape.x + ball->Shape.width);
            float prediction = ball->Shape.y;

            if (distanceX > 0.0f && speedX > 0.01f) {
                const float time = distanceX / speedX;
                prediction = ball->Shape.y + ball->Velocity.y * time;

                while (prediction < 0.0f || prediction > maxY) {
                    if (prediction < 0.0f) {
                        prediction = -prediction;
                    } else if (prediction > maxY) {
                        prediction = 2.0f * maxY - prediction;
                    }
                }
            }

            const float errorRange = 16.0f + (speedX * 0.05f);
            const float error = ((float)GetRandomValue(-(int)errorRange, (int)errorRange));
            paddle->targetY = prediction + error;
            reactionTimer = 0.12f;
        }
    } else {
        paddle->targetY = maxY * 0.5f;
        reactionTimer = 0.0f;
    }

    paddle->targetY = fminf(maxY, fmaxf(0.0f, paddle->targetY));
    const float delta = paddle->targetY - paddle->Shape.y;
    const float maxStep = Speed * dt;
    if (fabsf(delta) <= maxStep) {
        paddle->Shape.y = paddle->targetY;
    } else {
        paddle->Shape.y += (delta > 0.0f ? 1.0f : -1.0f) * maxStep;
    }

    // Keep paddle inside screen bounds (safety check)
    paddle->Shape.y = fminf(maxY, fmaxf(0.0f, paddle->Shape.y));
}

void DrawPaddle(const Paddle *paddle) {
    DrawRectangle((int)paddle->Shape.x, (int)paddle->Shape.y, (int)paddle->Shape.width, (int)paddle->Shape.height, paddle->PaddleColor);
}
