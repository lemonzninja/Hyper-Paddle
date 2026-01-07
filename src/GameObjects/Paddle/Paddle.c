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
    // Clamp target position to screen bounds
    const float screenHeight = (float) GetScreenHeight();

    const float dead_zone = 5.0f;
    const float dt = deltaTime();

    const float paddle_center_y = rect_center_y(&paddle->Shape);
    const float ball_center_y = rect_center_y(&ball->Shape);

    // Positive offset means ball is below paddle
    const float offset_y = ball_center_y - paddle_center_y;

    // Apply a vertical step
    paddle->Shape.y += ai_vertical_step(offset_y, Speed, dt, dead_zone);

    // Keep paddle inside screen bounds (safety check)
    if (paddle->Shape.y < 0)
    {
        paddle->Shape.y = 0;
    }
    if (paddle->Shape.y + paddle->Shape.height > screenHeight)
    {
        paddle->Shape.y = screenHeight - paddle->Shape.height;
    }
}

void DrawPaddle(const Paddle *paddle) {
    DrawRectangle((int)paddle->Shape.x, (int)paddle->Shape.y, (int)paddle->Shape.width, (int)paddle->Shape.height, paddle->PaddleColor);
}