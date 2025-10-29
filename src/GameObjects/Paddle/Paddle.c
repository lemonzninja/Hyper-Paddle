/****************************************************************
*              - Paddle Game Object -
*  Created by Squid on 10/28/2025.
****************************************************************/

#include "GameObjects/Paddle/Paddle.h"



void InitPaddle(Paddle *paddle, const float x, const float y, const float width, const float height, const Color paddleColor) {
    paddle->Shape.x = x;
    paddle->Shape.y = y;
    paddle->Shape.width = width;
    paddle->Shape.height = height;
    paddle->PaddleColor = paddleColor;
}

void UpdatePaddle(Paddle* paddle) {

}

void DrawPaddle(const Paddle *paddle) {
    DrawRectangle((int)paddle->Shape.x, (int)paddle->Shape.y,
                    (int)paddle->Shape.width, (int)paddle->Shape.height, paddle->PaddleColor);
}