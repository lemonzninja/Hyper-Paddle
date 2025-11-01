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

float playerPaddleX = 45;
float playerPaddleY = 299;
float playerPaddleWidth = 20;
float playerPaddleHeight = 80;
float PLayerSpeed = 200.f;
Color playerColor = WHITE;
Paddle playerPaddle;

float playerTwoPaddleX = 1200;
float playerTwoPaddleY = 299;
float playerTwoPaddleWidth = 20;
float playerTwoPaddleHeight = 80;
Color playerTwoColor = WHITE;
Paddle playerTwoPaddle;

void InitMainGame() {
    // Init the player Paddle.
    InitPaddle(&playerPaddle, playerPaddleX, playerPaddleY, playerPaddleWidth, playerPaddleHeight, playerColor);
    // Init the AI Paddle.
    InitPaddle(&playerTwoPaddle, playerTwoPaddleX, playerTwoPaddleY, playerTwoPaddleWidth, playerTwoPaddleHeight,
               playerTwoColor);

    // Init the ball in the center of the screen.
    ballX = (float)GetScreenWidth() / 2.0f - ballRadius;
    ballY = (float)GetScreenHeight() / 2.0f - ballRadius;

    // Start the ball at the top of the screen and in the center
    ballY = 60;
    InitBall(&ball, ballX, ballY, ballRadius * 2, ballRadius * 2, ballSpeed, ballColor);
}

void UpdateMainGame() {
    UpdatePlayerPaddle(&playerPaddle, PLayerSpeed);
    UpdateBall(&ball);

    HandleHorizontalBounds(&ball);
}

void drawMainGame() {
    DrawPaddle(&playerPaddle);
    // DrawPaddle(&playerTwoPaddle);
    DrawBall(&ball);
}