/****************************************************************
*              - Paddle Game Object -
*  Created by Squid on 10/28/2025.
****************************************************************/

#include "GameObjects/Paddle/Paddle.h"
#include "Systems/deltaTime.h"
#include "Systems/KeybordManager/KeybordManager.h"



void InitPaddle(Paddle *paddle, const float x, const float y, const float width, const float height, const Color paddleColor) {
    paddle->Shape.x = x;
    paddle->Shape.y = y;
    paddle->Shape.width = width;
    paddle->Shape.height = height;
    paddle->PaddleColor = paddleColor;
}

void UpdatePaddle(Paddle* paddle) {

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
}


void DrawPaddle(const Paddle *paddle) {
    DrawRectangle((int)paddle->Shape.x, (int)paddle->Shape.y,
                    (int)paddle->Shape.width, (int)paddle->Shape.height, paddle->PaddleColor);
}
