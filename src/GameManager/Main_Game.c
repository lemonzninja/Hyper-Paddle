/****************************************************************
*              - The Main game -
*   All the logic of the Main game goes here.
*  Created by Squid on 10/29/2025
****************************************************************/
#include "Game_Manager.h"

static GameScreen nextScreen;

// Game configuration constants
static const float BALL_SPEED = 450.0f;
static const float BALL_RADIUS = 10.0f;
static const float PLAYER_PADDLE_SPEED = 400.0f;
static const float AI_PADDLE_SPEED = 390.0f;
static const float SCORE_SIZE = 30.0f;
static const int WIN_SCORE = 5;

// Score display
static Counter playerScoreText;
static Counter aiScoreText;

// Ball
static Ball ball;
static float ballResetX;
static float ballResetY;

// Paddles
static Paddle playerPaddle;
static Paddle aiPaddle;
typedef enum {WINNER_NONE, WINNER_PLAYER, WINNER_AI} Winner;
static bool gameOver = false;
static Winner winner = WINNER_NONE;

static UIButton restartButton;
static UIButton menuButton;


void InitMainGame(void) {
    nextScreen = SCREEN_MAIN_GAME;

    // Calculate ball reset position
    ballResetX = (float)GetScreenWidth() / 2.0f - BALL_RADIUS;
    ballResetY = 200.0f;

    // Initialize ball (loads sound resource)
    InitBall(&ball, ballResetX, ballResetY, BALL_RADIUS * 2, BALL_RADIUS * 2, BALL_SPEED, WHITE);

    // Initialize UI buttons (one-time setup)
    InitUiButton(&restartButton, (float)GetScreenWidth() / 2 - 150, (float)GetScreenHeight() / 2,
                 100, 50, LIGHTGRAY, WHITE, GRAY, BLACK);
    InitUiButton(&menuButton, (float)GetScreenWidth() / 2 + 50, (float)GetScreenHeight() / 2,
                 100, 50, LIGHTGRAY, WHITE, GRAY, BLACK);

    // Reset game state
    ResetMainGame();
}

void ResetMainGame(void) {
    // Reset scores
    InitScore(&playerScoreText, 0,
              (float)GetScreenWidth() / 2.f - 50.f, 30.f,
              WHITE, SCORE_SIZE);
    InitScore(&aiScoreText, 0,
              (float)GetScreenWidth() / 2.f + 50.f, 30.f,
              WHITE, SCORE_SIZE);

    // Reset paddles to starting positions
    InitPaddle(&playerPaddle, 45, 299, 20, 80, WHITE);
    InitPaddle(&aiPaddle, 1200, 299, 20, 80, WHITE);

    // Reset ball
    ResetBall(&ball, ballResetX, ballResetY, BALL_SPEED);

    // Reset game state
    gameOver = false;
    winner = WINNER_NONE;
}

void UnloadMainGame(void) {
    UnloadBall(&ball);
}

static void ResetBallAfterScore(Ball* ball, const bool launchTowardsLeft) {
    ball->Shape.x = ballResetX;
    ball->Velocity.x = launchTowardsLeft ? BALL_SPEED : -BALL_SPEED;
}

static void HandleBallPaddleCollision(Ball* ball, const Paddle* paddle, const bool isRightPaddle) {
    if (CheckCollisionRecs(ball->Shape, paddle->Shape)) {
        if (isRightPaddle) {
            ball->Shape.x = paddle->Shape.x - ball->Shape.width;
        } else {
            ball->Shape.x = paddle->Shape.x + paddle->Shape.width;
        }
        ball->Velocity.x = -ball->Velocity.x;
    }
}

void UpdateMainGame(void) {
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
    UpdatePlayerPaddle(&playerPaddle, PLAYER_PADDLE_SPEED);
    UpdateAIPaddle(&aiPaddle, AI_PADDLE_SPEED, &ball);
    // Move Ball
    UpdateBall(&ball);

    // The Ball Paddle Collisions
    HandleBallPaddleCollision(&ball, &playerPaddle, false); // The player collision.
    HandleBallPaddleCollision(&ball, &aiPaddle, true); // The AI collision.

    HandleVerticalBounds(&ball);

    ballDetectGoal(&ball);

    if (ball.isLeftSide) {
        aiScoreText.score += 1;
        ball.isLeftSide = false;
        ResetBallAfterScore(&ball, false);
        // Check Ai WIN condition
        if (aiScoreText.score >= WIN_SCORE) {
            gameOver = true;
            winner = WINNER_AI;
        }
    }

    if (ball.isRightSide) {
        playerScoreText.score += 1;
        ball.isRightSide = false;
        ResetBallAfterScore(&ball, true);
        // Check Player WIN condition
        if (playerScoreText.score >= WIN_SCORE) {
            gameOver = true;
            winner = WINNER_PLAYER;
        }
    }
}

void drawMainGame(void) {
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