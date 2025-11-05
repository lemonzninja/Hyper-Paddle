/****************************************************************
*              - The Main game -
*   All the logic of the Main game goes here.
*  Created by Squid on 10/29/2025
****************************************************************/

#include <stdio.h>

#include "Game_Manager.h"
#include "GameObjects/Paddle/Paddle.h"
#include "GameObjects/Ball/Ball.h"
#include "Systems/ScoreManager/ScoreManager.h"

// score variables
Counter playerScoreText;
float playerScoreX;
float playerScoreY;
float playerScoreSize;
Color playerScoreColor;
int playerScore;

Counter aiScoreText;
float aiScoreX;
float aiScoreY;
float aiScoreSize;
Color aiScoreColor;
int aiScore;

Ball ball;
float ballRadius = 10;
float ballX = 0;
float ballY = 0;
float ballSpeed = 300.0f;
Color ballColor = WHITE;

float ballResetX = 0;
float ballResetY = 0;

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

    playerScoreX = (float)GetScreenWidth() / 2.f - 50.f;
    playerScoreY = 30.f;
    playerScoreSize = 30.f;
    playerScoreColor = WHITE;
    playerScore = 0;

    aiScoreX = (float) GetScreenWidth() / 2.f + 50.f;
    aiScoreY = 30.f;
    aiScoreSize = 30.f;
    aiScoreColor = WHITE;
    aiScore = 0;

    // Init the player Paddle.
    InitPaddle(&playerPaddle, playerPaddleX, playerPaddleY, playerPaddleWidth, playerPaddleHeight, playerColor);
    // Init the AI Paddle.
    InitPaddle(&AIPaddle, aiTwoPaddleX, aiTwoPaddleY, aiTwoPaddleWidth, aiPaddleHeight,
               playerTwoColor);

    // Init the ball in the center of the screen.
    ballX = (float)GetScreenWidth() / 2.0f - ballRadius;
    ballY = (float)GetScreenHeight() / 2.0f - ballRadius;

    // ball re-star pos
    ballResetX = (float)GetScreenWidth() / 2.0f - ballRadius;
    ballResetY = (float)GetScreenHeight() / 2.0f - ballRadius;

    // Start the ball at the top of the screen and in the center
    ballY = 200;
    InitBall(&ball, ballX, ballY, ballRadius * 2, ballRadius * 2, ballSpeed, ballColor);

    // init the score for player one
    InitScore(&playerScoreText,playerScore, playerScoreX, playerScoreY, playerScoreColor, "0", playerScoreSize);
    InitScore(&aiScoreText, aiScore, aiScoreX, aiScoreY, aiScoreColor, "0", aiScoreSize);
}

static void ResetBallAfterScore(Ball* scoredBall, const bool launchTowardsLeft) {
    scoredBall->Shape.x = ballResetX;
    scoredBall->Shape.y = ballResetY;

    float absoluteVelocityX = scoredBall->Velocity.x;
    if (absoluteVelocityX < 0.0f) {
        absoluteVelocityX = -absoluteVelocityX;
    }
    if (absoluteVelocityX == 0.0f) {
        absoluteVelocityX = ballSpeed;
    }

    scoredBall->Velocity.x = launchTowardsLeft ? absoluteVelocityX : -absoluteVelocityX;
}

void HandleBallPaddleCollision(Ball* ball, const Paddle* paddle, const bool isRightPaddle) {
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
    HandleBallPaddleCollision(&ball, &playerPaddle, false); // The player collision.
    HandleBallPaddleCollision(&ball, &AIPaddle, true); // The AI collision.

    //HandleHorizontalBounds(&ball);
    HandleVerticalBounds(&ball);

    UpdateGameScore(&ball);

    if (ball.isLefSide) {
        aiScore += 1;
        ball.isLefSide = false;
        ResetBallAfterScore(&ball, false);
    }

    if (ball.isRightSide) {
        playerScore += 1;
        ball.isRightSide = false;
        ResetBallAfterScore(&ball, true);
    }


    //ball.Velocity.x = ballSpeed;
    //ball.Velocity.y = ballSpeed;
    //ball.isLefSide = false;


}


void drawMainGame() {
    DrawScore(&playerScoreText, playerScore, playerScoreSize, playerScoreColor);
    DrawScore(&aiScoreText, aiScore, aiScoreSize, aiScoreColor);

    DrawPaddle(&playerPaddle);
    DrawPaddle(&AIPaddle);

    DrawBall(&ball);
}


