/****************************************************************
*              - The Main game -
*   All the logic of the Main game goes here.
*  Created by Squid on 10/29/2025
****************************************************************/

#include <stdio.h>
#include "Game_Manager.h"
#include "Systems/deltaTime.h"

// score variables
Counter playerScoreText;
Counter aiScoreText;
float scoreSize;
int scoreToAdd;
int newScore;
Color scoreTextColor;

// ball variables
Ball ball;
float ballRadius;
float ballSpeed;
Color ballColor;
float ballResetX;
float ballResetY;

// player paddle
Paddle playerPaddle;
float PLayerSpeed;

// Ai paddle
Paddle aiPaddle;
float aiPaddleSpeed;

void InitMainGame() {
    scoreToAdd = 0;
    newScore = 1;

    scoreSize = 30.f;
    scoreTextColor = WHITE;

    playerScoreText.position.x = (float)GetScreenWidth() / 2.f - 50.f;
    playerScoreText.position.y = 30.f;
    playerScoreText.textSize = scoreSize;
    playerScoreText.textColor = scoreTextColor;
    playerScoreText.score = scoreToAdd;

    //aiScore = aiScoreText.score;
    aiScoreText.position.x = (float) GetScreenWidth() / 2.f + 50.f;
    aiScoreText.position.y = 30.f;
    aiScoreText.textSize = scoreSize;
    aiScoreText.textColor = scoreTextColor;
    aiScoreText.score = scoreToAdd;

    ballRadius = 10;
    ballSpeed = 350.0f;
    ballColor = WHITE;
    ballResetX = (float)GetScreenWidth() / 2.0f - ballRadius;;
    ballResetY = 200;
    ball.Shape.x = 0;
    ball.Shape.y = 0;

    playerPaddle.Shape.x = 45;
    playerPaddle.Shape.y = 299;
    playerPaddle.Shape.width = 20;
    playerPaddle.Shape.height = 80;
    playerPaddle.PaddleColor = WHITE;
    PLayerSpeed = 400.f;

    aiPaddle.Shape.x = 1200;
    aiPaddle.Shape.y = 299;
    aiPaddle.Shape.width = 20;
    aiPaddle.Shape.height = 80;
    aiPaddle.PaddleColor = WHITE;
    aiPaddleSpeed = 321.0f;

    // init player score
    InitScore(&playerScoreText, playerScoreText.score, playerScoreText.position.x, playerScoreText.position.y, playerScoreText.textColor, playerScoreText.textSize);
    InitScore(&aiScoreText, aiScoreText.score, aiScoreText.position.x, aiScoreText.position.y, aiScoreText.textColor, scoreSize);

    // Init the player Paddle.
    InitPaddle(&playerPaddle, playerPaddle.Shape.x, playerPaddle.Shape.y, playerPaddle.Shape.width, playerPaddle.Shape.height, playerPaddle.PaddleColor);
    // Init the AI Paddle.
    InitPaddle(&aiPaddle, aiPaddle.Shape.x, aiPaddle.Shape.y, aiPaddle.Shape.width, aiPaddle.Shape.height,
               aiPaddle.PaddleColor);

    // Init the ball in the center of the screen.
    ball.Shape.x = (float)GetScreenWidth() / 2.0f - ballRadius;
    ball.Shape.y = 200;

    // ball re-star pos
    //ballResetX = (float)GetScreenWidth() / 2.0f - ballRadius;
    //ballResetY = (float)GetScreenHeight() / 2.0f - ballRadius;

    InitBall(&ball, ball.Shape.x, ball.Shape.y, ballRadius * 2, ballRadius * 2, ballSpeed, ballColor);
}

static void ResetBallAfterScore(Ball* ball, const bool launchTowardsLeft) {
    ball->Shape.x = ballResetX;

    float absoluteVelocityX = ball->Velocity.x;

    if (absoluteVelocityX < 0.0f) {
        absoluteVelocityX = -absoluteVelocityX * ballSpeed * 0.5f;
    }
    if (absoluteVelocityX == 0.0f) {
        absoluteVelocityX = ballSpeed * deltaTime();
    }

    ball->Velocity.x = (float)launchTowardsLeft * deltaTime() ? ballSpeed : -ballSpeed;
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
    UpdateAIPaddle(&aiPaddle, aiPaddleSpeed);
    // Move Ball
    UpdateBall(&ball);

    // The Ball Paddle Collisions
    HandleBallPaddleCollision(&ball, &playerPaddle, false); // The player collision.
    HandleBallPaddleCollision(&ball, &aiPaddle, true); // The AI collision.

    HandleVerticalBounds(&ball);

    UpdateGameScore(&ball);

    if (ball.isLeftSide) {
        aiScoreText.score += newScore;
        ball.isLeftSide = false;
        ResetBallAfterScore(&ball, false);
    }

    if (ball.isRightSide) {
        playerScoreText.score += newScore;
        ball.isRightSide = false;
        ResetBallAfterScore(&ball, true);
    }
}


void drawMainGame() {
    DrawScore(&playerScoreText);
    DrawScore(&aiScoreText);

    DrawPaddle(&playerPaddle);
    DrawPaddle(&aiPaddle);

    DrawBall(&ball);
}


