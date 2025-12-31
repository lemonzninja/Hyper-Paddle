/****************************************************************
*              - The Main game -
*   All the logic of the Main game goes here.
*  Created by Squid on 10/29/2025
****************************************************************/
#include "Game_Manager.h"

extern bool gameShouldClose;

static GameScreen nextScreen;

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

// Game over state
static const int WIN_SCORE = 10;
typedef enum {WINNER_NONE, WINNER_PLAYER, WINNER_AI} Winner;
static bool gameOver = false;
static Winner winner = WINNER_NONE;

UIButton restartButton;
UIButton menuButton;


void InitMainGame() {
    nextScreen = SCREEN_MAIN_GAME;

    // Initialize Resources that need to be loaded

    // Ball.
    ballSpeed = 450.0f;
    ballRadius = 10;
    ballColor = WHITE;
    ballResetX = (float)GetScreenWidth() / 2.0f - ballRadius;
    ballResetY = 200;

    // InitBall loads the sound.
    InitBall(&ball, ballResetX, ballResetY, ballRadius * 2, ballRadius * 2, ballSpeed, ballColor);

    // Reset the rest of the game state.
    ResetMainGame();
}

void ResetMainGame(void) {
    // The number of points to add to the score.
    newScore = 1;
    // Score Stuff.
    scoreSize = 30.f;
    scoreTextColor = WHITE;
    // Player Score text.
    playerScoreText.position.x = (float)GetScreenWidth() / 2.f - 50.f;
    playerScoreText.position.y = 30.f;
    playerScoreText.textSize = scoreSize;
    playerScoreText.textColor = scoreTextColor;
    playerScoreText.score  = 0;
    // Ai Score text.
    aiScoreText.position.x = (float) GetScreenWidth() / 2.f + 50.f;
    aiScoreText.position.y = 30.f;
    aiScoreText.textSize = scoreSize;
    aiScoreText.textColor = scoreTextColor;
    aiScoreText.score = 0;

    // Player Paddle.
    playerPaddle.Shape.x = 45;
    playerPaddle.Shape.y = 299;
    playerPaddle.Shape.width = 20;
    playerPaddle.Shape.height = 80;
    playerPaddle.PaddleColor = WHITE;
    PLayerSpeed = 400.f;
    // AI Paddle.
    aiPaddle.Shape.x = 1200;
    aiPaddle.Shape.y = 299;
    aiPaddle.Shape.width = 20;
    aiPaddle.Shape.height = 80;
    aiPaddle.PaddleColor = WHITE;
    aiPaddleSpeed = 370.0f;

    InitUiButton(&restartButton, (float)GetScreenWidth() / 2 - 150, (float)GetScreenHeight() / 2, 100, 50, LIGHTGRAY, WHITE, GRAY,
                 BLACK);
    InitUiButton(&menuButton, (float)GetScreenWidth() / 2 + 50, (float)GetScreenHeight() / 2, 100, 50, LIGHTGRAY, WHITE, GRAY, BLACK);

    // init player score.
    InitScore(&playerScoreText, playerScoreText.score, playerScoreText.position.x, playerScoreText.position.y, playerScoreText.textColor, playerScoreText.textSize);
    InitScore(&aiScoreText, aiScoreText.score, aiScoreText.position.x, aiScoreText.position.y, aiScoreText.textColor, scoreSize);

    // Init the player Paddle.
    InitPaddle(&playerPaddle, playerPaddle.Shape.x, playerPaddle.Shape.y, playerPaddle.Shape.width, playerPaddle.Shape.height, playerPaddle.PaddleColor);
    // Init the AI Paddle.
    InitPaddle(&aiPaddle, aiPaddle.Shape.x, aiPaddle.Shape.y, aiPaddle.Shape.width, aiPaddle.Shape.height,
               aiPaddle.PaddleColor);

    // Reset game state scores.
    gameOver = false;
    winner = WINNER_NONE;
    playerScoreText.score = 0;
    aiScoreText.score = 0;

    // Reset the ball state (position, velocity)
    ResetBall(&ball, ballResetX, ballResetY, ballSpeed);
}

void UnloadMainGame(void) {
    UnloadBall(&ball);
}

static void ResetBallAfterScore(Ball* ball, const bool launchTowardsLeft) {
    ball->Shape.x = ballResetX;

    float absoluteVelocityX = ball->Velocity.x;

    if (absoluteVelocityX < 0.0f) {
        absoluteVelocityX = -absoluteVelocityX;
    }
    if (absoluteVelocityX == 0.0f) {
        absoluteVelocityX = ballSpeed;
    }

    ball->Velocity.x = launchTowardsLeft ? ballSpeed : -ballSpeed;
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
    // If game over, pause gameplay and wait for user input
    if (gameOver) {
        UpdateUiButton(&restartButton);
        UpdateUiButton(&menuButton);

        if (IsUiButtonClicked(&restartButton)) {
            ResetMainGame();
        }

        if (IsUiButtonClicked(&menuButton)) {
            nextScreen = SCREEN_MENU;
        }
        return;
    }

    // Move Paddles
    UpdatePlayerPaddle(&playerPaddle, PLayerSpeed);
    UpdateAIPaddle(&aiPaddle, aiPaddleSpeed, &ball);
    // Move Ball
    UpdateBall(&ball);

    // The Ball Paddle Collisions
    HandleBallPaddleCollision(&ball, &playerPaddle, false); // The player collision.
    HandleBallPaddleCollision(&ball, &aiPaddle, true); // The AI collision.

    HandleVerticalBounds(&ball);

    ballDetectGoal(&ball);

    if (ball.isLeftSide) {
        aiScoreText.score += newScore;
        ball.isLeftSide = false;
        ResetBallAfterScore(&ball, false);
        // Check Ai WIN condition
        if (aiScoreText.score >= WIN_SCORE) {
            gameOver = true;
            winner = WINNER_AI;
        }
    }

    if (ball.isRightSide) {
        playerScoreText.score += newScore;
        ball.isRightSide = false;
        ResetBallAfterScore(&ball, true);
        // Check Player WIN condition
        if (playerScoreText.score >= WIN_SCORE) {
            gameOver = true;
            winner = WINNER_PLAYER;
        }
    }
}


void drawMainGame() {
    ClearBackground(BLACK);

    DrawScore(&playerScoreText);
    DrawScore(&aiScoreText);

    DrawPaddle(&playerPaddle);
    DrawPaddle(&aiPaddle);

    DrawBall(&ball);

    // Draw overlay if the game is over.
    if (gameOver) {
        const Color menuBackgroundColor = DARKBLUE;
        const Rectangle menuBackground = {
            (float)GetScreenWidth() / 2.0f - 200,
            (float)GetScreenHeight() / 2.0f - 50,
            400,
            150
        };
        DrawRectangle((int)menuBackground.x, (int)menuBackground.y,
                      (int)menuBackground.width, (int)menuBackground.height,
                      menuBackgroundColor);

        // Draw "GAME OVER" text
        const char *gameOverText = "GAME OVER";
        const int gameOverFontSize = 40;
        int textWidth = MeasureText(gameOverText, gameOverFontSize);
        DrawText(gameOverText,
                 menuBackground.x + (menuBackground.width - (float)textWidth) / 2,
                 (int)menuBackground.y - 20,
                 gameOverFontSize, WHITE);

        // Draw winner announcement
        const char *winnerText = winner == WINNER_PLAYER ? "Player Wins!" : "AI Wins!";
        const int winnerFontSize = 30;
        textWidth = MeasureText(winnerText, winnerFontSize);
        DrawText(winnerText,
                 menuBackground.x + (menuBackground.width - (float)textWidth) / 2,
                 (int)menuBackground.y - 60,
                 winnerFontSize, WHITE);

        DrawUiButton(&restartButton, "Restart", 20);
        DrawUiButton(&menuButton, "Exit", 20);
    }
}

GameScreen GetMenuScreen(void) {
    return nextScreen;
}
