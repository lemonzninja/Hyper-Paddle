/****************************************************************
*              - The Manager of the game -
*  Created by Squid on 10/29/2025
****************************************************************/

#include "Game_Manager.h"
#include "GameObjects/Paddle/Paddle.h"

float deltaTime = 0;

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
    InitPaddle(&playerPaddle, playerPaddleX, playerPaddleY, playerPaddleWidth, playerPaddleHeight, playerColor);
    InitPaddle(&playerTwoPaddle, playerTwoPaddleX, playerTwoPaddleY, playerTwoPaddleWidth, playerTwoPaddleHeight,
               playerTwoColor);
}

void UpdateMainGame() {
    deltaTime = GetFrameTime();

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        playerPaddle.Shape.y -= PLayerSpeed * deltaTime;
    }

    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        playerPaddle.Shape.y += PLayerSpeed * deltaTime;
    }
}

void drawMainGame() {
    DrawPaddle(&playerPaddle);
    DrawPaddle(&playerTwoPaddle);
}