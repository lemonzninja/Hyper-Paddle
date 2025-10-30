/****************************************************************
*              - The Manager of the game -
*  Created by Squid on 10/29/2025
****************************************************************/

#include "Game_Manager.h"
#include "GameObjects/Paddle/Paddle.h"
#include "Systems/deltaTime.h"
#include "Systems/KeybordManager/KeybordManager.h"

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


    if (IsUpPressed()) {
        playerPaddle.Shape.y -= PLayerSpeed * deltaTime();
    }

    if (IsDownPressed()) {
        playerPaddle.Shape.y += PLayerSpeed * deltaTime();
    }
}

void drawMainGame() {
    DrawPaddle(&playerPaddle);
    DrawPaddle(&playerTwoPaddle);
}