/****************************************************************
*              - The Manager of the game -
*  Created by Squid on 10/29/2025
****************************************************************/

#include "Game_Manager.h"
#include "GameObjects/Paddle/Paddle.h"
#include "GameObjects/Ball/Ball.h"



Ball ball;
float ballRadius = 10;
float ballX = 0;
float ballY = 0;
float ballSpeed = 50.0f;
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
    ballX = GetScreenWidth() / 2.0f - ballRadius;
    ballY = GetScreenHeight() / 2.0f - ballRadius;
    InitBall(&ball, ballX, ballY, ballRadius * 2, ballRadius * 2, ballSpeed, ballColor);
}

void UpdateMainGame() {
    UpdatePlayerPaddle(&playerPaddle, 10);
    UpdateBall(&ball);
}

void drawMainGame() {
    DrawPaddle(&playerPaddle);
    DrawPaddle(&playerTwoPaddle);
    DrawBall(&ball);
}


