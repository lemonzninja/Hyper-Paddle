/****************************************************************
*              - The Main game -
*   All the logic of the Main game goes here.
*  Created by Squid on 10/29/2025
****************************************************************/

#include "Game_Manager.h"
#include "GameObjects/Paddle/Paddle.h"
#include "GameObjects/Ball/Ball.h"

Ball ball;
float ballRadius = 10;
float ballX = 0;
float ballY = 0;
float ballSpeed = 300.0f;
Color ballColor = WHITE;

Paddle playerPaddle;
float playerPaddleX = 45;
float playerPaddleY = 299;
float playerPaddleWidth = 20;
float playerPaddleHeight = 80;
float PLayerSpeed = 400.f;
Color playerColor = WHITE;

Paddle AIPaddle;
float aiTwoPaddleX = 1200;
float aiTwoPaddleY = 299;
float aiTwoPaddleWidth = 20;
float aiPaddleHeight = 80;
float aiPaddleSpeed = 450.0f;
Color playerTwoColor = WHITE;

void InitMainGame() {
    // Init the player Paddle.
    InitPaddle(&playerPaddle, playerPaddleX, playerPaddleY, playerPaddleWidth, playerPaddleHeight, playerColor);
    // Init the AI Paddle.
    InitPaddle(&AIPaddle, aiTwoPaddleX, aiTwoPaddleY, aiTwoPaddleWidth, aiPaddleHeight,
               playerTwoColor);

    // Init the ball in the center of the screen.
    ballX = (float)GetScreenWidth() / 2.0f - ballRadius;
    ballY = (float)GetScreenHeight() / 2.0f - ballRadius;

    // Start the ball at the top of the screen and in the center
    ballY = 200;
    InitBall(&ball, ballX, ballY, ballRadius * 2, ballRadius * 2, ballSpeed, ballColor);
}

void HandleBallPaddleCollision(Ball *ball, const Paddle *paddle, bool isRightPaddle) {
    if (CheckCollisionRecs(ball->Shape, paddle->Shape)) {
        if (isRightPaddle) {
            ball->Shape.x = paddle->Shape.x - ball->Shape.width;
        } else {
            ball->Shape.x = paddle->Shape.x + paddle->Shape.width;
        }
        ball->Velocity.x = -ball->Velocity.x;
    }
}

void UpdateMainGame() {
    // Move Paddles
    UpdatePlayerPaddle(&playerPaddle, PLayerSpeed);
    UpdateAIPaddle(&AIPaddle, aiPaddleSpeed);
    // Move Ball
    UpdateBall(&ball);

    // The Ball Paddle Collisions
    HandleBallPaddleCollision(&ball, &playerPaddle, false);
    HandleBallPaddleCollision(&ball, &AIPaddle, true);

    HandleHorizontalBounds(&ball);
    HandleVerticalBounds(&ball);
}

void drawMainGame() {
    DrawPaddle(&playerPaddle);
    DrawPaddle(&AIPaddle);

    DrawBall(&ball);
}